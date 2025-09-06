#pragma once
#include"clsScreen.h";
#include"clsCurrency.h";
#include"clsInputValidate.h";
class clsFindCurrencyScreen : protected clsScreen {
	static void _PrintCurrency(clsCurrency Currency) {
		cout << clsUtility::Tab(5) << "Currency Card\n";
		cout << clsUtility::Tab(5) << "------------------------------------\n";
		cout << clsUtility::Tab(5) << " Country       : " << Currency.Country()<< endl;
		cout << clsUtility::Tab(5) << " Currency Name : " << Currency.CurrencyName() << endl;
		cout << clsUtility::Tab(5) << " Currency Code : " << Currency.CurrencyCode() << endl;
		cout << clsUtility::Tab(5) << " Rate(1$)      : " << Currency.Rate() << endl;
		cout << clsUtility::Tab(5) << "------------------------------------\n";
	}
	static void _ReadChoice() {
		short Choice = 0;
		cout << clsUtility::Tab(5) << "Find By: [1] Code, [2] Country ? : ";
		Choice = clsInputValidate::ReadIntNumberBetween(1, 2, "\t\t\t\t\tPlease Enter Number 1 or 2 : ");
		if (Choice == 1) {
			cout << clsUtility::Tab(5) << "Please Enter Currency Code : ";
			string CurrencyCode = clsInputValidate::ReadString();
			while (!clsCurrency::IsExistCurrencyCode(CurrencyCode)) {
				cout << clsUtility::Tab(5) << "Currency Code Not Found.\n";
				cout << clsUtility::Tab(5) << "Please Enter Currency Code : ";
				CurrencyCode = clsInputValidate::ReadString();
			}
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			cout << clsUtility::Tab(5) << "Currency Found :-)\n";
			_PrintCurrency(Currency);

		}
		else if (Choice == 2) {
			cout << clsUtility::Tab(5) << "Please Enter Country : ";
			string Country = clsInputValidate::ReadString();
			while (!clsCurrency::IsExistCountry(Country)) {
				cout << clsUtility::Tab(5) << "Country Not Found.\n";
				cout << clsUtility::Tab(5) << "Please Enter Country : ";
				Country = clsInputValidate::ReadString();
			}
			clsCurrency Currency2 = clsCurrency::FindByCountry(Country);
			cout << clsUtility::Tab(5) << "Currency Found :-)\n";
			_PrintCurrency(Currency2);
		}
	}
public:
	static void ShowFindCurrencyScreen() {
		_PrintHeaderScreen("Find Currency Screen");
		_ReadChoice();
	}
};