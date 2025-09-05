#pragma once
#include"clsScreen.h";
#include"clsUsers.h";
#include"clsAddUserScreen.h";
#include"clsUtility.h";

class clsUpdateUserScreen : protected clsScreen {
	static void _ReadUserData(clsUsers& User) {
		cout << endl << clsUtility::Tab(5) << "Please Enter First Name      : ";
		User.FirstName = clsInputValidate::ReadString();

		cout << endl << clsUtility::Tab(5) << "Please Enter Last Name       : ";
		User.LastName = clsInputValidate::ReadString();

		cout << endl << clsUtility::Tab(5) << "Please Enter Email           : ";
		User.Email = clsInputValidate::ReadString();

		cout << endl << clsUtility::Tab(5) << "Please Enter Phone           : ";
		User.Phone = clsInputValidate::ReadString();

		cout << endl << clsUtility::Tab(5) << "Please Enter Password        : ";
		User.Password = clsInputValidate::ReadString();
		User.Password = clsUtility::EncryptText(User.Password);

		cout << endl;
		User.Permissions = clsAddUserScreen::_ReadPermissions(User);
	}
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
		cout << clsUtility::Tab(5) << " Permissions  : " << User.Permissions << endl;
		cout << clsUtility::Tab(5) << "------------------------------------\n";
	}
	static void _UpdateUser() {
		cout << clsUtility::Tab(5) << "Please Enter Username : ";
		string Username = clsInputValidate::ReadString();
		while (!clsUsers::IsUserExist(Username)) {
			cout << clsUtility::Tab(5) << "Client With Username ["<<Username<<"] Does Not Exist\n";
			cout << clsUtility::Tab(5) << "Please Enter Username : ";
			Username = clsInputValidate::ReadString();
		}
		clsUsers User = clsUsers::Find(Username);
		_PrintUser(User);
		char Ensure = 'n';
		cout << clsUtility::Tab(5) << "Are You Sure You Want To Update This User ? Y/N : ";
		cin >> Ensure;
		if (tolower(Ensure) == 'y') {
			_ReadUserData(User);
			clsUsers::enSave Save = User.Save();
			switch (Save) {
			case clsUsers::enSave::SvFailed_Empty:
				cout << endl << clsUtility::Tab(5) << "Failed Update.\n";
				break;
			case clsUsers::enSave::SvSucceeded:
				cout << endl << clsUtility::Tab(5) << "User Updated Successfully\n";
				_PrintUser(User);
				break;
			}
		}
	}
public:
	static void ShowUpdateUserScreen() {
		_PrintHeaderScreen("Update User Screen");
		_UpdateUser();
	}
};

