#pragma once
#include"clsScreen.h";
#include"clsBankClient.h";
#include"Global.h";
class clsUpdateClientScreen : protected clsScreen {
	static void _ReadClientData(clsBankClient& Client) {
		cout << endl << clsUtility::Tab(5) << "Please Enter First Name      : ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << endl << clsUtility::Tab(5) << "Please Enter Last Name       : ";
		Client.LastName = clsInputValidate::ReadString();

		cout << endl << clsUtility::Tab(5) << "Please Enter Email           : ";
		Client.Email = clsInputValidate::ReadString();

		cout << endl << clsUtility::Tab(5) << "Please Enter Phone           : ";
		Client.Phone = clsInputValidate::ReadString();

		cout << endl << clsUtility::Tab(5) << "Please Enter PINCode         : ";
		Client.PINCode = clsInputValidate::ReadString();

		cout << endl << clsUtility::Tab(5) << "Please Enter Account Balance : ";
		Client.AccountBalance = clsInputValidate::ReadDBLNumber();
	}
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
	static void _UpdateClient() {
		cout << clsUtility::Tab(5) << "Please Enter Account Number : ";
		string AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << clsUtility::Tab(5) << "Client With Account Number Does Not Exist\n";
			cout << clsUtility::Tab(5) << "Please Enter Account Number : ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
		char Ensure = 'n';
		cout << clsUtility::Tab(5) << "Are You Sure You Want To Update This Client ? Y/N : ";
		cin >> Ensure;
		if (tolower(Ensure) == 'y') {
			_ReadClientData(Client);
			clsBankClient::enSave Save = Client.Save();
			switch (Save) {
			case clsBankClient::enSave::SvFailed_Empty:
				cout << endl << clsUtility::Tab(5) << "Failed Update.\n";
				break;
			case clsBankClient::enSave::SvSucceeded:
				cout << endl << clsUtility::Tab(5) << "Client Updated Successfully\n";
				_PrintClient(Client);
				break;
			}
		}
	}
public:
	static void ShowUpdateClientScreen() {
		if (_CheckPermission(clsUsers::enMainMenuPermission::PUpdateClient)) {
			return;
		}
		_PrintHeaderScreen("Update Client Screen");
		_UpdateClient();
	}
};

