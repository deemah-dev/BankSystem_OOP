#pragma once
#include"clsScreen.h";
#include"clsBankClient.h";
#include"clsInputValidate.h";
class clsTransferScreen : protected clsScreen {
	static void _PrintClientCard(clsBankClient Client) {
		cout << clsUtility::Tab(5) << "Client Card\n";
		cout << clsUtility::Tab(5) << "------------------------------------\n";
		cout << clsUtility::Tab(5) << " Full Name    : " << Client.FullName() << endl;
		cout << clsUtility::Tab(5) << " Acc. Number  : " << Client.AccountNumber() << endl;
		cout << clsUtility::Tab(5) << " Acc. Balance : " << Client.AccountBalance << endl;
		cout << clsUtility::Tab(5) << "------------------------------------\n";
	}
	static string _ReadAccountNumber(string FromOrTo) {
		cout << clsUtility::Tab(5) << "Please Enter Account Number To Transfer "<< FromOrTo <<" : ";
		string AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << clsUtility::Tab(5) << "Client With Account Number [" << AccountNumber << "] Does-Not Exist\n";
			cout << clsUtility::Tab(5) << "Please Enter Account Number To Transfer " << FromOrTo << " : ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}
	static double ReadAmount(clsBankClient Client) {
		cout << clsUtility::Tab(5) << "Enter Transfer Amount : ";
		double Amount = clsInputValidate::ReadDBLNumber();
		while (Amount > Client.AccountBalance) {
			cout << clsUtility::Tab(5) << "Amount exceeds Balance\n";
			cout << clsUtility::Tab(5) << "You can transfer from " << to_string(Client.AccountBalance) << endl;
			cout << clsUtility::Tab(5) << "Enter Transfer Amount : ";
			Amount = clsInputValidate::ReadDBLNumber();
		}
		return Amount;
	}
public:
	static void ShowTransferScreen() {
		_PrintHeaderScreen("Transfer Screen");
		string AccountNumber1 = _ReadAccountNumber("From");
		clsBankClient SourceClient = clsBankClient::Find(AccountNumber1);
		_PrintClientCard(SourceClient);

		string AccountNumber2 = _ReadAccountNumber("To");
		clsBankClient DestinationClient = clsBankClient::Find(AccountNumber2);
		_PrintClientCard(DestinationClient);

		double Amount = ReadAmount(SourceClient);

		char Ensure = 'n';
		cout << clsUtility::Tab(5) << "Are you sure you want to perform this operation? : ";
		cin >> Ensure;
		if (tolower(Ensure) == 'y') {
			SourceClient.Transfer(DestinationClient, Amount, CurrentUser.Username);

			cout << clsUtility::Tab(5) << "Transfer done successfully\n\n";
			_PrintClientCard(SourceClient);
			cout << endl;
			_PrintClientCard(DestinationClient);
			cout << endl;
		}
		else
			return;
	}
};