#pragma once
#include"clsScreen.h";
#include"clsUtility.h";
#include"clsCurrenciesListScreen.h";
#include"clsFindCurrencyScreen.h";
#include"clsUpdateRateScreen.h";
#include"clsCurrencyCalculatorScreen.h";
class clsCurrencyExchangeMainScreen : protected clsScreen {
	static short _ReadCurrencyExchangeMenuChoice() {
		cout << "\t\t\t\t\tChoose what do you want to do : ";
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 5, "\t\t\t\t\tPlease enter a number Between 1 to 5 : ");
		return Choice;
	}
	enum enCurrencyExchange { ListCurrencies = 1, FindCurrency = 2, UpdateRate = 3, CurrencyCalculator = 4, MainMenu = 5 };
	static void _GoBackToCurrencyExchangeMenu() {
		cout << endl << clsUtility::Tab(5) << "\tPress any key to back to currency exchange menu . . . ";
		system("pause>0");
		ShowCurrencyExchangeMainScreen();
	}

	static void _ShowCurrenciesListScreen() {
		/*cout << "Currencies list screen will be here.\n";*/
		clsCurrenciesListScreen::ShowCurrenciesList();
	}
	static void _ShowFindCurrencyScreen() {
		/*cout << "Find currency screen will be here.\n";*/
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}
	static void _ShowUpdateRateScreen() {
		/*cout << "Update Rate screen will be here.\n";*/
		clsUpdateRateScreen::ShowUpdateRateScreen();
	}
	static void _ShowCurrencyCalculatorScreen() {
		/*cout << "Currency calculator screen will be here.\n";*/
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}
	static void _GetTheProcessInCurrencyExchangeMenu(enCurrencyExchange Choice) {
		switch (Choice) {
		case enCurrencyExchange::ListCurrencies:
			system("cls");
			_ShowCurrenciesListScreen();
			_GoBackToCurrencyExchangeMenu();
			break;
		case enCurrencyExchange::FindCurrency:
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyExchangeMenu();
			break;
		case enCurrencyExchange::UpdateRate:
			system("cls");
			_ShowUpdateRateScreen();
			_GoBackToCurrencyExchangeMenu();
			break;
		case enCurrencyExchange::CurrencyCalculator:
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrencyExchangeMenu();
		case enCurrencyExchange::MainMenu:
			break;
		}
	}
public:
	static void ShowCurrencyExchangeMainScreen() {
		system("cls");
		_PrintHeaderScreen("Currency Exchange Main Screen");
		cout << clsUtility::Tab(5) << "==========================================\n";
		cout << clsUtility::Tab(7) << "Currency Exchange Menu\n";
		cout << clsUtility::Tab(5) << "==========================================\n";
		cout << clsUtility::Tab(5) << "[1] List Currencies\n";
		cout << clsUtility::Tab(5) << "[2] Find Currency\n";
		cout << clsUtility::Tab(5) << "[3] Update Rate\n";
		cout << clsUtility::Tab(5) << "[4] Currency Calculator\n";
		cout << clsUtility::Tab(5) << "[5] Main Menu\n";
		cout << clsUtility::Tab(5) << "===========================================\n";
		_GetTheProcessInCurrencyExchangeMenu((enCurrencyExchange)_ReadCurrencyExchangeMenuChoice());
	}
};