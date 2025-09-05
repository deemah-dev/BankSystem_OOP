#pragma once
#include"clsScreen.h";
#include"clsBankClient.h";
#include"clsMainScreen.h";
#include"clsDepositScreen.h";
#include"clsWithdrawScreen.h";
#include"clsTotalBalancesScreen.h";
#include"clsTransferScreen.h";
#include"clsTransferListScreen.h";
#include"Global.h";
class clsTransactionsScreen : protected clsScreen {
	static short _ReadTransactionsMenuChoice() {
		cout << "\t\t\t\t\tChoose what do you want to do : ";
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 6, "\t\t\t\t\tPlease enter a number Between 1 to 6 : ");
		return Choice;
	}
	enum enTransactionsMenu { Deposit = 1, Withdraw = 2, TotalBalances = 3, Transfer = 4, TransferList = 5, MainMenu = 6 };
	static void _GoBackToTransactionsMenu() {
		cout << "Press any key to back to Transactions Menu . . .";
		system("pause>0");
		ShowTransactionsMenu();
	}

	static void _ShowDepositScreen() {
		/*cout << "Deposit Screen Will Be Here\n";*/
		clsDepositScreen::ShowDepositScreen();
	}
	static void _ShowWithdrawScreen() {
		/*cout << "Withdraw Screen Will Be Here\n";*/
		clsWithdrawScreen::ShowWithdrawScreen();
	}
	static void _ShowTotalBalancesScreen() {
		/*cout << "TotalBalances Screen Will Be Here\n";*/
		clsTotalBalancesScreen::ShowBalancesList();
	}
	static void _ShowTransferScreen() {
		/*cout << "Transfer Screen Will Be Here\n";*/
		clsTransferScreen::ShowTransferScreen();
	}
	static void _ShowTransferListScreen() {
		/*cout << "Transfer list will be here\n";*/
		clsTransferListScreen::ShowTransferListScreen();
	}

	static void _GetTheProcessInTransactionsMenu(enTransactionsMenu Choice) {
		switch (Choice) {
		case enTransactionsMenu::Deposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenu();
			break;

		case enTransactionsMenu::Withdraw:
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenu();
			break;

		case enTransactionsMenu::TotalBalances:
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenu();
			break;
		case enTransactionsMenu::Transfer:
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenu();
			break;
		case enTransactionsMenu::TransferList:
			system("cls");
			_ShowTransferListScreen();
			_GoBackToTransactionsMenu();
			break;
		case enTransactionsMenu::MainMenu:
			break;
		}
	}

public:
	static void ShowTransactionsMenu() {
		system("cls");
		if (_CheckPermission(clsUsers::enMainMenuPermission::PTransactions)) {
			return;
		}
		_PrintHeaderScreen("Transactions Screen");
		cout << clsUtility::Tab(5) << "==========================================\n";
		cout << clsUtility::Tab(6) << "Transactions Menu Screen\n";
		cout << clsUtility::Tab(5) << "==========================================\n";
		cout << clsUtility::Tab(5) << "[1] Deposit\n";
		cout << clsUtility::Tab(5) << "[2] Withdraw\n";
		cout << clsUtility::Tab(5) << "[3] Total Balances\n";
		cout << clsUtility::Tab(5) << "[4] Transfer\n";
		cout << clsUtility::Tab(5) << "[5] Transfer List\n";
		cout << clsUtility::Tab(5) << "[6] Main Menu\n";
		cout << clsUtility::Tab(5) << "==========================================\n";
		_GetTheProcessInTransactionsMenu((enTransactionsMenu)_ReadTransactionsMenuChoice());
	}
};