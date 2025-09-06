#pragma once
#include"clsScreen.h";
#include"clsInputValidate.h";
#include"clsClientsListScreen.h";
#include"clsAddClientScreen.h";
#include"clsDeleteClientScreen.h";
#include"clsUpdateClientScreen.h";
#include"clsFindClientScreen.h";
#include"clsTransactionsScreen.h";
#include"clsManageUsersScreen.h";
#include"clsLoginRegisterListScreen.h";
#include"clsCurrencyExchangeMainScreen.h";
#include"clsLoginScreen.h";
#include"Global.h";
class clsMainScreen : public clsScreen {
	static short _ReadMainMenuChoice() {
		cout << "\t\t\t\t\tChoose what do you want to do : ";
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 10, "\t\t\t\t\tPlease enter a number Between 1 to 10 : ");
		return Choice;
	}
	enum enMainMenu { ShowClients = 1, AddClient = 2, DeleteClient = 3, UpdateClient = 4, FindClient = 5, Transactions = 6, ManageUsers = 7,LoginRegister = 8,CurrencyExchange = 9, Logout = 10 };
	static void _GoBackToMainMenu() {
		cout <<endl<<clsUtility::Tab(5) << "\tPress any key to back to main menu . . . ";
		system("pause>0");
		ShowMainScreen();
	}

	static void _ShowClientsListScreen() {
		/*cout << "Client List Screen Will Be Here\n";*/
		clsClientsListScreen::ShowClientsList();
	}
	static void _ShowAddClientScreen() {
		/*cout << "Add Client Screen Will Be Here\n";*/
		clsAddClientScreen::ShowAddClientScreen();
	}
	static void _ShowDeleteClientScreen() {
		/*cout << "Delete Client Screen Will Be Here\n";*/
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}
	static void _ShowUpdateClientScreen() {
	/*	cout << "Update Client Screen Will Be Here\n";*/
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}
	static void _ShowFindClientScreen() {
		/*cout << "Find Client Screen Will Be Here\n";*/
		clsFindClientScreen::ShowFindClientScreen();
	}
	static void _ShowTransactionsMenu() {
		/*cout << "Transaction Screen Will Be Here\n";*/
		clsTransactionsScreen::ShowTransactionsMenu();

	}
	static void _ShowManageUsersMenu() {
		/*cout << "Manage Users Screen Will Be Here\n";*/
		clsManageUsersScreen::ShowManageUsersScreen();
	}
	static void _ShowLoginRegisterListScreen() {
		/*cout << "Login Register List Will Be Here\n";*/
		clsLoginRegisterListScreen::ShowLoginRegisterListScreen();
	}
	static void _ShowCurrencyExchangeScreen() {
		/*cout << "Currency Exchange Main Screen Will Be Here\n";*/
		clsCurrencyExchangeMainScreen::ShowCurrencyExchangeMainScreen();
	}
	static void _Login() {
		cout << "Login Screen Will Be Here\n";
		CurrentUser = clsUsers::Find("","");
		//clsLoginScreen::ShowLoginScreen(); cause Error (invalid use of incomplete type)(áÃä ÌÓã ÇáÏÇáÉ íÍÊÇÌ ÑÄíÉ ßÇãáÉ ÚäÏ ÇáÊÍáíá)
	}

	static void _GetTheProcessInMainMenu(enMainMenu Choice) {
		if (Choice == enMainMenu::ShowClients) {
			system("cls");
			_ShowClientsListScreen();
			_GoBackToMainMenu();
		}
		else if (Choice == enMainMenu::AddClient) {
			system("cls");
			_ShowAddClientScreen();
			_GoBackToMainMenu();
		}
		else if (Choice == enMainMenu::DeleteClient) {
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenu();
		}
		else if (Choice == enMainMenu::UpdateClient) {
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenu();
		}
		else if (Choice == enMainMenu::FindClient) {
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenu();
		}
		else if (Choice == enMainMenu::Transactions) {
			system("cls");
			_ShowTransactionsMenu();
			_GoBackToMainMenu();
		}
		else if (Choice == enMainMenu::ManageUsers) {
			system("cls");
			_ShowManageUsersMenu();
			_GoBackToMainMenu();
		}
		else if (Choice == enMainMenu::LoginRegister) {
			system("cls");
			_ShowLoginRegisterListScreen();
			_GoBackToMainMenu();
		}
		else if (Choice == enMainMenu::CurrencyExchange) {
			system("cls");
			_ShowCurrencyExchangeScreen();
			_GoBackToMainMenu();
		}
		else if (Choice == enMainMenu::Logout) {
			system("cls");
			_Login();
		}
	}

public:

	static void ShowMainScreen() {
		system("cls");
		_PrintHeaderScreen("Main Screen");
		cout << clsUtility::Tab(5) << "==========================================\n";
		cout << clsUtility::Tab(7) << "Main Menu Screen\n";
		cout << clsUtility::Tab(5) << "==========================================\n";
		cout << clsUtility::Tab(5) << "[1]  Show Clients List\n";
		cout << clsUtility::Tab(5) << "[2]  Add New Client\n";
		cout << clsUtility::Tab(5) << "[3]  Delete Client\n";
		cout << clsUtility::Tab(5) << "[4]  Update Client Info\n";
		cout << clsUtility::Tab(5) << "[5]  Find Client\n";
		cout << clsUtility::Tab(5) << "[6]  Transactions\n";
		cout << clsUtility::Tab(5) << "[7]  Manage Users\n";
		cout << clsUtility::Tab(5) << "[8]  Login Register\n";
		cout << clsUtility::Tab(5) << "[9]  Currency Exchange\n";
		cout << clsUtility::Tab(5) << "[10] Logout\n";
		cout << clsUtility::Tab(5) << "===========================================\n";
		_GetTheProcessInMainMenu((enMainMenu)_ReadMainMenuChoice());
	}
};