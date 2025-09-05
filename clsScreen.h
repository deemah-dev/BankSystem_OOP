#pragma once
#include<iostream>
#include"clsUtility.h";
#include"clsUsers.h";
#include"Global.h";
#include<string>
#include"clsDate.h";
using namespace std;
class clsScreen {
protected:
	static void _PrintHeaderScreen(string Title, string SubTitle = "") {
		cout << clsUtility::Tab(5) << "-----------------------------------------\n\n";
		cout << clsUtility::Tab(5) << setw(20 - Title.size() / 2) << "" << Title << endl << endl;
		if (SubTitle != "")
			cout << clsUtility::Tab(7) << SubTitle << endl << endl;
		cout << clsUtility::Tab(5) << "-----------------------------------------\n\n";
		cout << clsUtility::Tab(5) << "User : " << CurrentUser.Username << endl;
		cout << clsUtility::Tab(5) << "Date : "; clsDate Date = clsDate::GetSystemDate(); Date.Print(); cout << endl;
	}
	static bool _CheckPermission(clsUsers::enMainMenuPermission Permission) {
		if (!CurrentUser.CheckPermission(Permission)) {
			string Title = "Access Denied! Contact Your Admin";
			cout << clsUtility::Tab(5) << "-----------------------------------------\n\n";
			cout << clsUtility::Tab(5) << setw(20 - Title.size() / 2) << "" << Title << endl << endl;
			cout << clsUtility::Tab(5) << "-----------------------------------------\n\n";
			return 1;
		}
		else
			return 0;
	}
};

