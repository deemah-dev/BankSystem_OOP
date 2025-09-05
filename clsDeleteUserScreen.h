#pragma once
#include"clsScreen.h";
#include"clsUsers.h";
class clsDeleteUserScreen : protected clsScreen {
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
	static void ShowDeleteUserScreen() {
		_PrintHeaderScreen("Delete User screen");
		cout << clsUtility::Tab(5) << "Enter Username : ";
		string Username = clsInputValidate::ReadString();
		while (!clsUsers::IsUserExist(Username)) {
			cout << clsUtility::Tab(5) << "User with Username [" << Username << "] Not Found.\n";
			cout << clsUtility::Tab(5) << "Inter Username :  : ";
			Username = clsInputValidate::ReadString();
		}
		if (Username == "Admin") {
			cout << clsUtility::Tab(5) << "You Cant Delete Admin.\n";
		}
		else {
			clsUsers User = clsUsers::Find(Username);
			_PrintUser(User);
			char Sure = 'y';
			cout <<endl<<endl<< clsUtility::Tab(5) << "Are you sure you want to delete this User? : ";
			cin >> Sure;
			if (tolower(Sure) == 'y') {
				if (User.Delete()) {
					cout << endl << endl << clsUtility::Tab(5) << "User deleted successfully" << endl;
					_PrintUser(User);
				}
				else
					cout << endl << endl << clsUtility::Tab(5) << "Failed Deleted\n";
			}
		}
	}
};
