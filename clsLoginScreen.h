#pragma once
#include"clsScreen.h";
#include"Global.h";
#include"clsInputValidate.h";
#include"clsUsers.h";
#include"clsMainScreen.h";
#include<fstream>
#include<vector>
#include"clsUtility.h";
class clsLoginScreen : protected clsScreen {
	static bool _Login() {
		bool LoginFailed = 1;
		short Trial = 3;
		do {
			cout << clsUtility::Tab(5) << "Enter Username : ";
			string Username = clsInputValidate::ReadString();
			cout << endl;
			cout << clsUtility::Tab(5) << "Enter Password : ";
			string Password = clsInputValidate::ReadString();
			cout << endl;
			CurrentUser = clsUsers::Find(Username, Password);
			LoginFailed = CurrentUser.IsEmpty();
			if (LoginFailed) {
				cout << clsUtility::Tab(5) << "Invalid Username/Password\n";
				Trial--;
				cout << clsUtility::Tab(5) << "You have " << Trial << " to login\n\n";
				if (Trial == 0) {
					cout << clsUtility::Tab(5) << "You are locked after 3 failed trials\n";
					return 0;
				}
			}
		} while (LoginFailed);
		CurrentUser.SaveCurrentUserLogInfoToFile();
		clsMainScreen::ShowMainScreen();
	}
public:
	static bool ShowLoginScreen() {
		system("cls");
		_PrintHeaderScreen("Login Screen");
		return _Login();
	}
};
