#pragma once
#include"clsScreen.h";
#include"clsCurrency.h";
#include"clsUtility.h";
class clsUpdateRateScreen : protected clsScreen {
	static void _PrintCurrency(clsCurrency Currency) {
		cout << clsUtility::Tab(5) << "Currency Card\n";
		cout << clsUtility::Tab(5) << "------------------------------------\n";
		cout << clsUtility::Tab(5) << " Country       : " << Currency.Country() << endl;
		cout << clsUtility::Tab(5) << " Currency Name : " << Currency.CurrencyName() << endl;
		cout << clsUtility::Tab(5) << " Currency Code : " << Currency.CurrencyCode() << endl;
		cout << clsUtility::Tab(5) << " Rate(1$)      : " << Currency.Rate() << endl;
		cout << clsUtility::Tab(5) << "------------------------------------\n";
	}

public:
	static void ShowUpdateRateScreen() {
		_PrintHeaderScreen("Update Rate Screen");
		cout << clsUtility::Tab(5) << "Please Enter Currency Code : ";
		string CurrencyCode = clsInputValidate::ReadString();
		while (!clsCurrency::IsExistCurrencyCode(CurrencyCode)) {
			cout << clsUtility::Tab(5) << "Currency Code Not Found.\n";
			cout << clsUtility::Tab(5) << "Please Enter Currency Code : ";
			CurrencyCode = clsInputValidate::ReadString();
		}
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(Currency);
		cout << clsUtility::Tab(5) << "Are you sure you want to update the rate of this country? (y/n) : ";
		char Ensure = 'n';
		cin >> Ensure;
		if (tolower(Ensure) == 'y') {
			cout << clsUtility::Tab(5) << "Update Currency Rate\n";
			cout << clsUtility::Tab(5) << "-----------------------\n";
			cout << clsUtility::Tab(5) << "Enter New Rate : ";
			float NewRate = 0.0;
			cin >> NewRate;
			Currency.UpdateRate(NewRate);
			cout << clsUtility::Tab(5) << "Rate Updated Successfully.\n\n";
			_PrintCurrency(Currency);
		}

	}
};
