#pragma once
#include"clsScreen.h";
#include"clsCurrency.h";
#include"clsInputValidate.h";
class clsCurrencyCalculatorScreen : protected clsScreen {
	static void _PrintCurrency(clsCurrency Currency) {
		cout << clsUtility::Tab(5) << "------------------------------------\n";
		cout << clsUtility::Tab(5) << " Country       : " << Currency.Country() << endl;
		cout << clsUtility::Tab(5) << " Currency Name : " << Currency.CurrencyName() << endl;
		cout << clsUtility::Tab(5) << " Currency Code : " << Currency.CurrencyCode() << endl;
		cout << clsUtility::Tab(5) << " Rate(1$)      : " << Currency.Rate() << endl;
		cout << clsUtility::Tab(5) << "------------------------------------\n";
	}
	static clsCurrency _GetCurrency(string Message) {
		cout << clsUtility::Tab(5) << Message;
		string CurrencyCode = clsInputValidate::ReadString();
		while (!clsCurrency::IsExistCurrencyCode(CurrencyCode)) {
			cout << clsUtility::Tab(5) << "Currency Code Not Found.\n";
			cout << clsUtility::Tab(5) << Message;
			CurrencyCode = clsInputValidate::ReadString();
		}
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return Currency;
	}
	static float _ReadAmount() {
		cout << clsUtility::Tab(5) << "Enter Amount To Exchange : ";
		double Amount = clsInputValidate::ReadDBLNumber();
		return (float)Amount;
	}
	static void _PrintCalculationResult(clsCurrency Currency1, clsCurrency Currency2, float Amount) {
		cout << clsUtility::Tab(5) << "Convert From\n";
		_PrintCurrency(Currency1);
		float AmountInUSD = Currency1.ConvertToUSD(Amount);
		cout << clsUtility::Tab(5) << Amount << " " << Currency1.CurrencyCode() << " = " << AmountInUSD << "USD" << endl;
		if (Currency2.CurrencyCode() == "USD")
			return;
		cout << clsUtility::Tab(5) << "To\n";
		_PrintCurrency(Currency2);
		float AmountInCurrency2 = Currency1.ConvertToOtherCurrencies(Currency2, Amount);
		cout << clsUtility::Tab(5) << Amount << " " << Currency1.CurrencyCode() << " = " << AmountInCurrency2 << Currency2.CurrencyCode() << endl;
	}

public:
	static void ShowCurrencyCalculatorScreen() {
		char Ensure = 'n';
		do {
			system("cls");
			_PrintHeaderScreen("Currency Calculator Screen");
			clsCurrency Currency1 = _GetCurrency("Please Enter Currency1 Code : ");
			clsCurrency Currency2 = _GetCurrency("Please Enter Currency2 Code : ");
			float Amount = _ReadAmount();

			_PrintCalculationResult(Currency1, Currency2, Amount);
			cout << clsUtility::Tab(5) << "Do you want to do another calculation? : ";
			cin >> Ensure;
		} while (tolower(Ensure) == 'y');
	}

};

