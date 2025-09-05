#pragma once
#include"clsScreen.h";
#include"clsUsers.h";
class clsAddUserScreen : protected clsScreen {

	static short _ReadPermissions(clsUsers& User) {
		User.Permissions = 0;
		char  FullAccess;
		cout << clsUtility::Tab(5) << "Do you want to give full access? (y/n) : ";
		cin >> FullAccess;
		if (tolower(FullAccess) == 'y') {
			User.Permissions = clsUsers::enMainMenuPermission::PFullAccess;
			return User.Permissions;
		}
		else {
			char Answer = 'n';
			cout << clsUtility::Tab(5) << "Do you want to give access to :\n\n";
			cout << clsUtility::Tab(5) << "Show Client List? (y/n) : ";
			cin >> Answer;
			if (Answer == 'y') User.Permissions += clsUsers::enMainMenuPermission::PShowClients;

			cout << clsUtility::Tab(5) << "Add New Client? (y/n) : ";
			cin >> Answer;
			if (Answer == 'y') User.Permissions += clsUsers::enMainMenuPermission::PAddClient;

			cout << clsUtility::Tab(5) << "Delete Client? (y/n) : ";
			cin >> Answer;
			if (Answer == 'y') User.Permissions += clsUsers::enMainMenuPermission::PDeleteClient;

			cout << clsUtility::Tab(5) << "Update Client? (y/n) : ";
			cin >> Answer;
			if (Answer == 'y') User.Permissions += clsUsers::enMainMenuPermission::PUpdateClient;

			cout << clsUtility::Tab(5) << "Find Client? (y/n) : ";
			cin >> Answer;
			if (Answer == 'y') User.Permissions += clsUsers::enMainMenuPermission::PFindClient;

			cout << clsUtility::Tab(5) << "Transactions? (y/n) : ";
			cin >> Answer;
			if (Answer == 'y') User.Permissions += clsUsers::enMainMenuPermission::PTransactions;

			cout << clsUtility::Tab(5) << "Manage Users? (y/n) : ";
			cin >> Answer;
			if (Answer == 'y') User.Permissions += clsUsers::enMainMenuPermission::PManageUsers;

			cout << clsUtility::Tab(5) << "Show Login Register List? (y/n) : ";
			cin >> Answer;
			if (Answer == 'y') User.Permissions += clsUsers::enMainMenuPermission::PShowLoginRegisterInfoScreen;

			return User.Permissions;
		}
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
		cout << clsUtility::Tab(5) << " Permission   : " << User.Permissions << endl;
		cout << clsUtility::Tab(5) << "------------------------------------\n";
	}
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

		cout << endl;
		User.Permissions = _ReadPermissions(User);
	}
public:
	static void ShowAddUserScreen() {
		_PrintHeaderScreen("Add User Screen");
		cout << clsUtility::Tab(5) << "Inter Username : ";
		string Username = clsInputValidate::ReadString();
		if (clsUsers::IsUserExist(Username)) {
			cout << clsUtility::Tab(5) << "User with Username [" << Username << "] is already exist.\n";
			cout << clsUtility::Tab(5) << "Try another Username : ";
			Username = clsInputValidate::ReadString();
		}
		clsUsers User = clsUsers::AddNewUsername(Username);
		_ReadUserData(User);
		clsUsers::enSave Save = User.Save();
		switch (Save) {
		case clsUsers::enSave::SvFailed_Empty:
			cout << clsUtility::Tab(5) << "Failed Addition\n";
		case clsUsers::enSave::SvSucceeded:
			cout << clsUtility::Tab(5) << "Add User Successfully\n";
			_PrintUser(User);
		}
	}
	friend class clsUpdateUserScreen;
};
