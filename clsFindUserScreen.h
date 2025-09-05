#pragma once
#include"clsScreen.h";
#include"clsUsers.h";

class clsFindUserScreen : public clsScreen {
	static void _PrintUser(clsUsers User) {
		cout << clsUtility::Tab(5) << "User Card\n";
		cout << clsUtility::Tab(5) << "------------------------------------\n";
		cout << clsUtility::Tab(5) << " First Name   : " << User.FirstName << endl;
		cout << clsUtility::Tab(5) << " Last Name    : " << User.LastName << endl;
		cout << clsUtility::Tab(5) << " Full Name    : " << User.FullName() << endl;
		cout << clsUtility::Tab(5) << " Email        : " << User.Email << endl;
		cout << clsUtility::Tab(5) << " Phone        : " << User.Phone << endl;
		cout << clsUtility::Tab(5) << " Username     : " << User.Username << endl;
		cout << clsUtility::Tab(5) << " Password     : " << User.Password << endl;
		cout << clsUtility::Tab(5) << " Permission   : " << User.Permissions << endl;
		cout << clsUtility::Tab(5) << "------------------------------------\n";
	}
public:
	static void ShowFindUserScreen() {
		_PrintHeaderScreen("Find User Screen");
		cout << clsUtility::Tab(5) << "Enter Username : ";
		string Username = clsInputValidate::ReadString();
		while (!clsUsers::IsUserExist(Username)) {
			cout << clsUtility::Tab(5) << "User with Username [" << Username << "] Not Found.\n";
			cout << clsUtility::Tab(5) << "Enter Username :  : ";
			Username = clsInputValidate::ReadString();
		}
		clsUsers User = clsUsers::Find(Username);
		_PrintUser(User);
	}
};
