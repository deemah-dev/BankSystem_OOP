#pragma once
#include"clsScreen.h";
#include"clsBankClient.h";
#include"clsMainScreen.h";
#include"clsUsersListScreen.h";
#include"clsAddUserScreen.h";
#include"clsDeleteUserScreen.h";
#include"clsUpdateUserScreen.h";
#include"clsFindUserScreen.h";
#include"Global.h";
class clsManageUsersScreen : protected clsScreen {
	static short _ReadManageUsersMenuChoice() {
		cout << "\t\t\t\t\tChoose what do you want to do : ";
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 6, "\t\t\t\t\tPlease enter a number Between 1 to 7 : ");
		return Choice;
	}
	enum enManageUsersMenu { ShowUsers = 1, AddUser = 2, DeleteUser = 3, UpdateUser = 4, FindUser = 5, MainMenuForUser = 6 };
	static void _GoBackToManageUsersMenu() {
		cout << "\nPress any key to back to Manage Users Menu . . .";
		system("pause>0");
		ShowManageUsersScreen();
	}

	static void _ShowUsersListScreen() {
		/*cout << "Users List Screen Will Be Here\n";*/
		clsUsersListScreen::ShowUsersList();
	}
	static void _ShowAddUserScreen() {
		/*cout << "Add User Screen Will Be Here\n";*/
		clsAddUserScreen::ShowAddUserScreen();
	}
	static void _ShowDeleteUserScreen() {
		/*cout << "Delete User Screen Will Be Here\n";*/
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}
	static void _ShowUpdateUserScreen() {
		/*cout << "Update User Screen Will Be Here\n";*/
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}
	static void _ShowFindUserScreen() {
	/*	cout << "Find User Screen Will Be Here\n";*/
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _GetTheProcessInManageUsersMenu(enManageUsersMenu Choice) {
		if (Choice == enManageUsersMenu::ShowUsers) {
			system("cls");
			_ShowUsersListScreen();
			_GoBackToManageUsersMenu();
		}
		else if (Choice == enManageUsersMenu::AddUser) {
			system("cls");
			_ShowAddUserScreen();
			_GoBackToManageUsersMenu();
		}
		else if (Choice == enManageUsersMenu::DeleteUser) {
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenu();
		}
		else if (Choice == enManageUsersMenu::UpdateUser) {
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenu();
		}
		else if (Choice == enManageUsersMenu::FindUser) {
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUsersMenu();
		}
		else if (Choice == enManageUsersMenu::MainMenuForUser) {
		}
	}

public:
	static void ShowManageUsersScreen() {
		system("cls");
		if (_CheckPermission(clsUsers::enMainMenuPermission::PManageUsers)) {
			return;
		}
		_PrintHeaderScreen("Manage Users Screen");
		cout << clsUtility::Tab(5) << "==========================================\n";
		cout << clsUtility::Tab(6) << "Manage Users Menu Screen\n";
		cout << clsUtility::Tab(5) << "==========================================\n";
		cout << clsUtility::Tab(5) << "[1] List Users\n";
		cout << clsUtility::Tab(5) << "[2] Add New User\n";
		cout << clsUtility::Tab(5) << "[3] Delete User\n";
		cout << clsUtility::Tab(5) << "[4] Update User\n";
		cout << clsUtility::Tab(5) << "[5] Find User\n";
		cout << clsUtility::Tab(5) << "[6] Main Menu\n";
		cout << clsUtility::Tab(5) << "==========================================\n";
		_GetTheProcessInManageUsersMenu((enManageUsersMenu)_ReadManageUsersMenuChoice());
	}
};
