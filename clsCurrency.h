#pragma once
using namespace std;
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include"clsString.h";
#include"clsUtility.h";
class clsCurrency {
	enum enMode { EmptyMode = 1, UpdateMode = 2 };
	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;
	static string _ConvertCurrencyObjectToDataLine(clsCurrency Currency, string Delim = "#//#") {
		string Line = "";
		Line = Currency.Country() + Delim;
		Line += Currency.CurrencyCode() + Delim;
		Line += Currency.CurrencyName() + Delim;
		Line += to_string(Currency.Rate());
		return Line;
	}
	static void _SaveCurrenciesObjectToFile(vector <clsCurrency> vCurrencies) {
		fstream File;
		File.open("Currencies.txt", ios::out);
		if (File.is_open()) {
			string Line;
			for (clsCurrency C : vCurrencies) {
				Line = _ConvertCurrencyObjectToDataLine(C);
				File << Line << endl;
			}
			File.close();
		}
	}

	static clsCurrency _ConvertDataLineToCurrencyObject(string Line) {
		vector <string> vCurrencies = clsString::Split(Line, "#//#");
		return clsCurrency(enMode::UpdateMode, vCurrencies[0], vCurrencies[1], vCurrencies[2], stof(vCurrencies[3]));
	}
	static vector <clsCurrency> _LoadCurrenciesDataFromFile() {
		fstream File;
		vector <clsCurrency> vCurrencies;
		File.open("Currencies.txt", ios::in);
		if (File.is_open()) {
			string Line;
			while (getline(File, Line)) {
				clsCurrency Currency = _ConvertDataLineToCurrencyObject(Line);
				vCurrencies.push_back(Currency);
			}
			File.close();
		}
		return vCurrencies;
	}
	void _Update() {
		vector <clsCurrency> vCurrencies = _LoadCurrenciesDataFromFile();
		for (clsCurrency& C : vCurrencies) {
			if (C.Country() == Country()) {
				C = *this;
				break;
			}
		}
		_SaveCurrenciesObjectToFile(vCurrencies);
	}

	static clsCurrency _GetEmptyCurrencyObject() {
		return clsCurrency(enMode::EmptyMode, "", "", "", 0.0);
	}

public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate) {
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}
	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	string Country() {
		return _Country;
	}

	string CurrencyCode() {
		return _CurrencyCode;
	}

	string CurrencyName() {
		return _CurrencyName;
	}

	float Rate () {
		return _Rate;
	}
	void UpdateRate(float Rate) {
		_Rate = Rate;
		_Update();
	}

	static clsCurrency FindByCode(string CurrencyCode) {
		CurrencyCode = clsString::UpperAllLetters(CurrencyCode);
		fstream File;
		File.open("Currencies.txt", ios::in);
		if (File.is_open()) {
			string Line;
			while (getline(File, Line)) {
				clsCurrency Currency = _ConvertDataLineToCurrencyObject(Line);
				if (CurrencyCode == Currency.CurrencyCode()) {
					File.close();
					return Currency;
				}
			}
			File.close();
		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country) {
		Country = clsString::UpperAllLetters(Country);
		fstream File;
		File.open("Currencies.txt", ios::in);
		if (File.is_open()) {
			string Line;
			while (getline(File, Line)) {
				clsCurrency Currency = _ConvertDataLineToCurrencyObject(Line);
				if (Country == clsString::UpperAllLetters(Currency.Country())) {
					File.close();
					return Currency;
				}
			}
			File.close();
		}
		return _GetEmptyCurrencyObject();
	}

	static bool IsExistCurrencyCode(string CurrencyCode) {
		clsCurrency C = clsCurrency::FindByCode(CurrencyCode);
		return (!C.IsEmpty());
	}
	static bool IsExistCountry(string Country) {
		clsCurrency C = clsCurrency::FindByCountry(Country);
		return (!C.IsEmpty());
	}

	static vector <clsCurrency> GitCurrenciesList() {
		return _LoadCurrenciesDataFromFile();
	}

	float ConvertToUSD(float Amount) {
		return(float) Amount / Rate();
	}

	float ConvertToOtherCurrencies(clsCurrency Currency2, float Amount) {
		float AmountInUSD = ConvertToUSD(Amount);
		if (Currency2.CurrencyCode() == "USD")
			return AmountInUSD;
		return (float)AmountInUSD * Currency2.Rate();
	}
};
