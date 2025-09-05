#pragma once
#include"clsScreen.h";
#include"clsBankClient.h";
#include"Global.h";
class clsFindClientScreen : protected clsScreen {
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
	static void ShowFindClientScreen() {
		if (_CheckPermission(clsUsers::enMainMenuPermission::PFindClient)) {
			return;
		}
		_PrintHeaderScreen("Find Client Screen");
		cout << clsUtility::Tab(5) << "Please Enter Account Number : ";
		string AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << clsUtility::Tab(5) << "Client With Account Number Does Not Exist\n";
			cout << clsUtility::Tab(5) << "Please Enter Account Number : ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
	}
};

