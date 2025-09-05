#pragma once
#include"clsDate.h";
using namespace std;
class clsInputValidate {
public:
	static bool IsNumberBetween(int Num, int MinNum, int MaxNum) {
		return (Num >= MinNum && Num <= MaxNum);
	}

	static bool IsNumberBetween(double Num, double MinNum, double MaxNum) {
		return (Num >= MinNum && Num <= MaxNum);
	}

	static bool IsDateBetween(clsDate Date, clsDate StartDate, clsDate EndDate) {
		if (StartDate.IsAfter(EndDate)) clsDate::SwapDates(StartDate, EndDate);
		return !(clsDate::CompareDate(Date, StartDate) == clsDate::enResult::Before || clsDate::CompareDate(Date, EndDate) == clsDate::enResult::After);
	}

	static int ReadIntNumber(string InValidMessage = "Invalid Value, try again : ") {
		int num = 0;
		cin >> num;
		while (true) {
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << InValidMessage;
				cin >> num;
			}
			else
				return num;
		}
	}

	static int ReadIntNumberBetween(int MinNum, int MaxNum, string InValidMessage = "Invalid Value, try again : ") {
		int num = 0;
		num = ReadIntNumber(InValidMessage);
		while (!IsNumberBetween(num, MinNum, MaxNum)) {
			cout << InValidMessage;
			cin >> num;
		}
		return num;
	}

	static double ReadDBLNumber(string InValidMessage = "Invalid Value, try again : ") {
		double num = 0;
		while (true) {
			cin >> num;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << InValidMessage;
			}
			else
				return num;
		}
	}

	static double ReadDBLNumberBetween(double MinNum, double MaxNum, string InValidMessage = "Invalid Value, try again : ") {
		double num = 0;
		num = ReadDBLNumber(InValidMessage);
		while (!IsNumberBetween(num, MinNum, MaxNum)) {
			cout << InValidMessage;
			cin >> num;
		}
		return num;
	}

	static bool IsValidDate(clsDate Date) {
		return Date.IsValid();
	}

	static string ReadString() {
		string Str;
		getline(cin >> ws, Str);
		return Str;
	}
};