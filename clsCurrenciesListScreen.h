#pragma once
#include"clsScreen.h";
#include"clsCurrency.h";
#include<string>;
class clsCurrenciesListScreen : public clsScreen {
	static void _PrintCurrencyRecord(clsCurrency Currency) {
		cout << "\t| " << setw(30) << left << Currency.Country();
		cout << "| " << setw(8) << left << Currency.CurrencyCode();
		cout << "| " << setw(40) << left << Currency.CurrencyName();
		cout << "| " << setw(13) << left << to_string(Currency.Rate());
	}
public:
	static void ShowCurrenciesList() {
		vector <clsCurrency> vCurrencies = clsCurrency::GitCurrenciesList();
		_PrintHeaderScreen("Currencies List Screen", to_string(vCurrencies.size()) + " Currency");
		cout << "\n\t_______________________________________________________";
		cout << "__________________________________________________\n" << endl;
		cout << "\t| " << left << setw(30) << "Country";
		cout << "| " << left << setw(8) << "Code";
		cout << "| " << left << setw(40) << "Name";
		cout << "| " << left << setw(13) << "Rate/(1$)";
		cout << "\n\t_______________________________________________________";
		cout << "__________________________________________________\n" << endl;
		if (vCurrencies.size() == 0)
			cout << "\t\t\t\t\tNo Currencies Available\n";
		else {
			for (clsCurrency C : vCurrencies)
			{
				_PrintCurrencyRecord(C);
				cout << endl;
			}
			cout << "\n\t______________________________________________________";
			cout << "_____________________________________________________\n" << endl;
		}
	}
};
