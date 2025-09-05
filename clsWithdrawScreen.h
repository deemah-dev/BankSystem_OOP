#pragma once
#include"clsScreen.h";
#include"clsBankClient.h";
#include"clsInputValidate.h";
class clsWithdrawScreen : protected clsScreen {
	static void _PrintClient(clsBankClient Client) {
		cout << clsUtility::Tab(5) << "Client Card\n";
		cout << clsUtility::Tab(5) << "------------------------------------\n";
		cout << clsUtility::Tab(5) << " First Name   : " << Client.FirstName << endl;
		cout << clsUtility::Tab(5) << " Last Name    : " << Client.LastName << endl;
		cout << clsUtility::Tab(5) << " Full Name    : " << Client.FullName() << endl;
		cout << clsUtility::Tab(5) << " Email        : " << Client.Email << endl;
		cout << clsUtility::Tab(5) << " Phone        : " << Client.Phone << endl;
		cout << clsUtility::Tab(5) << " Acc. Number  : " << Client.AccountNumber() << endl;
		cout << clsUtility::Tab(5) << " PIN Code     : " << Client.PINCode << endl;
		cout << clsUtility::Tab(5) << " Acc. Balance : " << Client.AccountBalance << endl;
		cout << clsUtility::Tab(5) << "------------------------------------\n";
	}
public:
	static void ShowWithdrawScreen() {
		_PrintHeaderScreen("Withdraw Screen");
		vector <clsBankClient> vClientData = clsBankClient::GetClientsList();
		cout << clsUtility::Tab(5) << "Please Enter Account Number : ";
		string AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << endl << clsUtility::Tab(5) << "Client with account number (" << AccountNumber << ") Not Found." << endl;
			cout << clsUtility::Tab(5) << "Please Enter Account Number : ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
		double Amount = 0;
		cout << endl << endl << clsUtility::Tab(5) << "Please Enter Withdraw Amount : ";
		cin >> Amount;
		while (!Client.Withdraw(Amount)) {
			cout << clsUtility::Tab(5) << "Amount exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
			cout << clsUtility::Tab(5) << "Please Enter Withdraw Amount : ";
			cin >> Amount;
		}
		char Sure = 'y';
		cout << endl << endl << clsUtility::Tab(5) << "Are you sure you want to Perform this transaction? : ";
		cin >> Sure;
		if (Sure == 'y' || Sure == 'Y') {
			Client.Withdraw(Amount);
			cout << endl << endl << clsUtility::Tab(5) << "Done Successfully, New Balance : " << Client.AccountBalance << endl;
		}
		else
			cout << endl << endl << clsUtility::Tab(5) << "Failed Withdrawal" << endl;
	}
};