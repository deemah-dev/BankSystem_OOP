#pragma once
#pragma warning(disable :  4996 )
#include<ctime>
#include<iostream>
#include<vector>
#include<string>
#include<iomanip>
using namespace std;

class clsDate {
private:
	short _Day = 0, _Month = 0, _Year = 0;
	static vector <string> Split(string Str, string Delim) {
		short Pos = 0;
		string word = "";
		vector <string> VWords;
		while ((Pos = Str.find(Delim)) != std::string::npos) {
			word = Str.substr(0, Pos);
			if (word != "")
				VWords.push_back(word);
			Str.erase(0, Pos + Delim.length());
		}
		if (Str != "")
			VWords.push_back(Str);

		return VWords;
	}
	static string JoinString(vector <string> VWords, string Delim) {
		string S = "";
		for (string& s : VWords)
			S = S + s + Delim;
		return S.substr(0, S.length() - Delim.length());
	}
	static short DayOrder(short Year, short Month, short Day) {
		int a = (14 - Month) / 12;
		int y = Year - a;
		int m = Month + 12 * a - 2;
		int d = (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
		return d;
	}
	static short DayOrder(clsDate Date) {
		return DayOrder(Date.Year, Date.Month, Date.Day);
	}
	static void PrintMonthCalendar(short Year, short Month) {
		cout << "  ________________" << MonthName(Month) << "________________\n";
		cout << setw(5) << "Sun" << setw(5) << "Mon" << setw(5) << "Tue" << setw(5) << "Wed" << setw(5) << "Thu" << setw(5) << "Fri" << setw(5) << "Sat" << endl;
		short DayNumber = 1;
		short MaxDayNumber = NumberOfDaysInMonth(Year, Month);
		short DayOne = DayOrder(Year, Month, 1);
		int i;
		for (i = 0; i < DayOne; i++)
			cout << setw(5) << "    ";
		for (int j = 1; j <= MaxDayNumber; j++) {
			cout << setw(5) << j;
			if (++i == 7) {
				i = 0;
				cout << endl;
			}
		}
		cout << "\n  ___________________________________\n";
	}
	static void SwapDates(clsDate& Date1, clsDate& Date2) {
		clsDate Temp;
		Temp = Date1;
		Date1 = Date2;
		Date2 = Temp;
	}
	static bool IsWeekend(clsDate Date) {
		return (DayOrder(Date) == 5 || DayOrder(Date) == 6);
	}
	static bool IsBusinessDay(clsDate Date) {
		return !IsWeekend(Date);
	}
	enum enResult { Before = -1, Equal = 0, After = 1 };

public:
	clsDate() {
		time_t NowTime = time(0);
		tm* now = localtime(&NowTime);

		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}
	clsDate(string stDate) {
		vector <string> vDate = Split(stDate, "/");
		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}
	clsDate(short Day, short Month, short Year) {
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	clsDate(short TotalDays, short Year) {
		_Year = Year;
		_Month = 1;

		short MonthDays = 0;
		while (true) {
			MonthDays = NumberOfDaysInMonth(_Year, _Month);
			if (TotalDays > MonthDays) {
				_Month++;
				TotalDays -= MonthDays;
			}
			else {
				_Day = TotalDays;
				break;
			}
		}
	}

	void SetDay(short Day) {
		_Day = Day;
	}
	short GetDay() {
		return _Day;
	}
	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month) {
		_Month = Month;
	}
	short GetMonth() {
		return _Month;
	}
	__declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(short Year) {
		_Year = Year;
	}
	short GetYear() {
		return _Year;
	}
	__declspec(property(get = GetYear, put = SetYear)) short Year;

	void Print() {
		cout << ToString() << endl;
	}

	void PrintMonthCalendar() {
		cout << "  ________________" << MonthName(_Month) << "________________\n";
		cout << setw(5) << "Sun" << setw(5) << "Mon" << setw(5) << "Tue" << setw(5) << "Wed" << setw(5) << "Thu" << setw(5) << "Fri" << setw(5) << "Sat" << endl;
		short DayNumber = 1;
		short MaxDayNumber = NumberOfDaysInMonth(_Year, _Month);
		short DayOne = DayOrder(_Year, _Month, 1);
		int i;
		for (i = 0; i < DayOne; i++)
			cout << setw(5) << "    ";
		for (int j = 1; j <= MaxDayNumber; j++) {
			cout << setw(5) << j;
			if (++i == 7) {
				i = 0;
				cout << endl;
			}
		}
		cout << "\n  ___________________________________\n";
	}

	void PrintYearCalendar() {
		cout << "  ___________________________________\n\n";
		cout << "\t\t " << _Year << "\n";
		cout << "  ___________________________________\n\n";
		for (int i = 1; i <= 12; i++) {
			PrintMonthCalendar(_Year, i);
			cout << endl;
		}
		cout << "  ___________________________________\n";
	}

	bool IsValid() {
		return (clsDate::Month >= 1 && clsDate::Month <= 12) && (clsDate::Day >= 1 && clsDate::Day <= NumberOfDaysInMonth(clsDate::Year, clsDate::Month));
	}

	static clsDate GetSystemDate() {
		time_t NowTime = time(0);
		tm* now = localtime(&NowTime);

		short Day = 0, Month = 0, Year = 0;
		Day = now->tm_mday;
		Month = now->tm_mon + 1;
		Year = now->tm_year + 1900;

		return clsDate(Day, Month, Year);
	}

	static bool IsLeapYear(short Year) {
		return (Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0;
	}
	bool IsLeapYear() {
		return IsLeapYear(_Day);
	}

	static short NumberOfDaysInMonth(short Year, short Month) {
		if (Month < 1 || Month > 12)
			return 0;
		short NumberOdDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : NumberOdDays[Month - 1]);
	}
	short NumberOfDaysInMonth() {
		return NumberOfDaysInMonth(_Year, _Month);
	}

	static bool IsLastDay(clsDate Date) {
		return (Date.Day == NumberOfDaysInMonth(Date.Year, Date.Month)) ? 1 : 0;
	}
	bool IsLastDay() {
		return IsLastDay(*this);
	}

	static bool IsLastMonth(short Month) {
		return (Month == 12) ? 1 : 0;
	}
	bool IsLastMonth() {
		return IsLastMonth(_Month);
	}

	static short GetDiff(clsDate Date1, clsDate Date2, bool InEndDay = 0) {
		short DiffNum = 0;
		short SwapFlagValue = 1;
		if (!IsDate1BeforeDate2(Date1, Date2)) {
			SwapFlagValue = -1;
			SwapDates(Date1, Date2);
		}
		while (IsDate1BeforeDate2(Date1, Date2)) {
			Date1 = IncreaseDateByOneDay(Date1);
			DiffNum++;
		}
		InEndDay ? ++DiffNum : DiffNum;
		return DiffNum * SwapFlagValue;
	}
	short GetDiff(clsDate Date2, bool InEndDay = 0) {
		return GetDiff(*this, Date2, InEndDay);
	}

	static short CalculateAgeByDays(clsDate Date1, bool InEndDay = 0) {
		short DiffNum = 0;
		clsDate Date2;
		Date2.GetSystemDate();
		while (IsDate1BeforeDate2(Date1, Date2)) {
			Date1 = IncreaseDateByOneDay(Date1);
			DiffNum++;
		}
		return InEndDay ? ++DiffNum : DiffNum;
	}
	short CalculateAgeByDays(bool InEndDay = 0) {
		return CalculateAgeByDays(*this, InEndDay);
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2) {
		return (Date1.Year < Date2.Year) ? 1 :
			(Date1.Year == Date2.Year) ?
			((Date1.Month < Date2.Month) ? 1 : ((Date1.Month == Date2.Month) ? ((Date1.Day < Date2.Day) ? 1 : 0) : 0)) : 0;
	}
	bool IsBefore(clsDate Date2) {
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsEqualDate(clsDate Date1, clsDate Date2) {
		return ((Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? 1 : 0) : 0) : 0);
	}
	bool IsEqual(clsDate Date2) {
		return IsEqualDate(*this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2) {
		return !IsDate1BeforeDate2(Date1, Date2) && !IsEqualDate(Date1, Date2);
	}
	bool IsAfter(clsDate Date2) {
		return IsDate1AfterDate2(*this, Date2);
	}

	static short GetVocationDays(clsDate Date1, clsDate Date2) {
		short VocationDays = 0;
		while (IsDate1BeforeDate2(Date1, Date2)) {
			if (IsBusinessDay(Date1))
				VocationDays++;
			Date1 = IncreaseDateByOneDay(Date1);
		}
		return VocationDays;
	}
	short GetVocationDays(clsDate Date2) {
		return GetVocationDays(*this, Date2);
	}

	static short GetBusinessDays(clsDate Date1, clsDate Date2) {
		return GetVocationDays(Date1, Date2);
	}
	short GetBusinessDays(clsDate Date2) {
		return GetBusinessDays(*this, Date2);
	}

	static clsDate CalculateVocationEndDate(clsDate Date1, clsDate Date2, short VocationDays) {
		return IncreaseDateByXDays(Date1, GetVocationDays(Date1, Date2));
	}
	void CalculateVocationEndDate(clsDate Date2, short VocationDays) {
		*this = CalculateVocationEndDate(*this, Date2, VocationDays);
	}

	static enResult CompareDate(clsDate Date1, clsDate Date2) {
		enResult Result;
		if (IsDate1BeforeDate2(Date1, Date2)) return Result = enResult::Before;
		else if (IsEqualDate(Date1, Date2)) return Result = enResult::Equal;
		/*else if (IsDate1AfterDate2(Date1, Date2)) return Result = enResult::After;*/
		return Result = enResult::After;
	}
	enResult CompareDate(clsDate Date2) {
		return CompareDate(*this, Date2);
	}

	static string DateToString(clsDate Date, string Delim = "/") {
		vector <string> vDate;
		vDate.push_back(to_string(Date.Day));
		vDate.push_back(to_string(Date.Month));
		vDate.push_back(to_string(Date.Year));
		return JoinString(vDate, Delim);
	}
	string ToString(string Delim = "/") {
		return DateToString(*this, Delim);
	}

	static short TotalDaysFromTheBeginningOfTheYear(clsDate Date) {
		short DaysCounter = 0;
		for (int i = 1; i < Date.Month; i++) {
			DaysCounter += NumberOfDaysInMonth(Date.Year, i);
		}
		DaysCounter += Date.Day;

		return DaysCounter;
	}
	short TotalDaysFromTheBeginningOfTheYear() {
		return TotalDaysFromTheBeginningOfTheYear(*this);
	}

	static string GetDayName(short DayNum) {
		string DaysName[7] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return DaysName[DayNum];
	}
	string DayName() {
		return GetDayName(DayOrder(*this));
	}

	static string MonthName(short Month) {
		string MonthsName[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return MonthsName[Month - 1];
	}
	string MonthName() {
		return MonthName(_Month);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date) {
		return 6 - DayOrder(Date);
	}
	short DaysUntilTheEndOfWeek() {
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date) {
		return NumberOfDaysInMonth(Date.Year, Date.Month) - Date.Day;
	}
	short DaysUntilTheEndOfMonth() {
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date) {
		clsDate EndYearDate;
		EndYearDate.Year = Date.Year;
		EndYearDate.Month = 12;
		EndYearDate.Day = 31;
		return GetDiff(Date, EndYearDate, 1);
	}
	short DaysUntilTheEndOfYear() {
		return DaysUntilTheEndOfYear(*this);
	}

	//call by ref just to keep memory
	static clsDate IncreaseDateByOneDay(clsDate& Date) {
		if (IsLastDay(Date)) {
			Date.Day = 1;
			if (IsLastMonth(Date.Month)) {
				Date.Month = 1;
				Date.Year++;
			}
			else
				Date.Month++;
		}
		else
			Date.Day++;
		return Date;
	}
	void IncreaseDateByOneDay() {
		*this = IncreaseDateByOneDay(*this);
	}

	static clsDate IncreaseDateByXDays(clsDate& Date, short DaysNumber) {
		for (int i = 1; i <= DaysNumber; i++) {
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByXDays(short DaysNumber) {
		*this = IncreaseDateByXDays(*this, DaysNumber);
	}

	static clsDate IncreaseDateByOneWeek(clsDate& Date) {
		for (int i = 1; i <= 7; i++) {
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByOneWeek() {
		*this = IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(clsDate& Date, short WeeksNumber) {
		for (int i = 1; i <= WeeksNumber; i++) {
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void IncreaseDateByXWeeks(short WeeksNumber) {
		*this = IncreaseDateByXWeeks(*this, WeeksNumber);
	}

	static clsDate IncreaseDateByOneMonth(clsDate& Date) {
		if (Date.Month == 12) {
			Date.Month = 1;
			Date.Year++;
		}
		else
			Date.Month++;

		if (Date.Day > NumberOfDaysInMonth(Date.Year, Date.Month))
			Date.Day = NumberOfDaysInMonth(Date.Year, Date.Month);
		return Date;
	}
	void IncreaseDateByOneMonth() {
		*this = IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(clsDate& Date, short MonthsNumber) {
		for (int i = 1; i <= MonthsNumber; i++) {
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void IncreaseDateByXMonths(short MonthsNumber) {
		*this = IncreaseDateByXMonths(*this, MonthsNumber);
	}

	static clsDate IncreaseDateByOneYear(clsDate& Date) {
		Date.Year++;
		return Date;
	}
	void IncreaseDateByOneYear() {
		*this = IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate& Date, short YearsNumber) {
		for (int i = 1; i <= YearsNumber; i++) {
			Date = IncreaseDateByOneYear(Date);
		}
		return Date;
	}
	void IncreaseDateByXYears(short YearsNumber) {
		*this = IncreaseDateByXYears(*this, YearsNumber);
	}

	static clsDate IncreaseDateByXYearsFaster(clsDate& Date, short YearsNumber) {
		Date.Year += YearsNumber;
		return Date;
	}
	void IncreaseDateByXYearsFaster(short YearsNumber) {
		*this = IncreaseDateByXYearsFaster(*this, YearsNumber);
	}

	static clsDate IncreaseDateByOneDecade(clsDate& Date) {
		Date.Year += 10;
		return Date;
	}
	void IncreaseDateByOneDecade() {
		*this = IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(clsDate& Date, short DecadesNumber) {
		for (int i = 1; i <= DecadesNumber; i++) {
			Date = IncreaseDateByOneDecade(Date);
		}
		return Date;
	}
	void IncreaseDateByXDecades(short DecadesNumber) {
		*this = IncreaseDateByXDecades(*this, DecadesNumber);
	}

	static clsDate IncreaseDateByXDecadesFaster(clsDate& Date, short DecadesNumber) {
		Date.Year += (DecadesNumber * 10);
		return Date;
	}
	void IncreaseDateByXDecadesFaster(short DecadesNumber) {
		*this = IncreaseDateByXDecadesFaster(*this, DecadesNumber);
	}

	static clsDate IncreaseDateByOneCentury(clsDate& Date) {
		Date.Year += 100;
		return Date;
	}
	void IncreaseDateByOneCentury() {
		*this = IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate& Date) {
		Date.Year += 1000;
		return Date;
	}
	void IncreaseDateByOneMillennium() {
		*this = IncreaseDateByOneMillennium(*this);
	}

	static clsDate DecreaseDateByOneDay(clsDate& Date) {
		if (Date.Day == 1) {
			if (Date.Month == 1) {
				Date.Month = 12;
				Date.Day = NumberOfDaysInMonth(Date.Year, 12);
				Date.Year--;
			}
			else {
				Date.Month--;
				Date.Day = NumberOfDaysInMonth(Date.Year, Date.Month - 1);
			}
		}
		else
			Date.Day--;
		return Date;
	}
	void DecreaseDateByOneDay() {
		*this = DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate& Date, short DaysNumber) {
		for (int i = 1; i <= DaysNumber; i++) {
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByXDays(short DaysNumber) {
		*this = DecreaseDateByXDays(*this, DaysNumber);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date) {
		for (int i = 1; i <= 7; i++) {
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByOneWeek() {
		*this = DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate& Date, short WeeksNumber) {
		for (int i = 1; i <= WeeksNumber; i++) {
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void DecreaseDateByXWeeks(short WeeksNumber) {
		*this = DecreaseDateByXWeeks(*this, WeeksNumber);
	}

	static clsDate DecreaseDateByOneMonth(clsDate& Date) {
		if (Date.Month == 1) {
			Date.Month = 12;
			Date.Year--;
		}
		else
			Date.Month--;

		if (Date.Day > NumberOfDaysInMonth(Date.Year, Date.Month))
			Date.Day = NumberOfDaysInMonth(Date.Year, Date.Month);
		return Date;
	}
	void DecreaseDateByOneMonth() {
		*this = DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate& Date, short MonthsNumber) {
		for (int i = 1; i <= MonthsNumber; i++) {
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void DecreaseDateByXMonths(short MonthsNumber) {
		*this = DecreaseDateByXMonths(*this, MonthsNumber);
	}

	static clsDate DecreaseDateByOneYear(clsDate& Date) {
		Date.Year--;
		return Date;
	}
	void DecreaseDateByOneYear() {
		*this = DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate& Date, short YearsNumber) {
		for (int i = 1; i <= YearsNumber; i++) {
			Date = DecreaseDateByOneYear(Date);
		}
		return Date;
	}
	void DecreaseDateByXYears(short YearsNumber) {
		*this = DecreaseDateByXYears(*this, YearsNumber);
	}

	static clsDate DecreaseDateByXYearsFaster(clsDate& Date, short YearsNumber) {
		Date.Year -= YearsNumber;
		return Date;
	}
	void DecreaseDateByXYearsFaster(short YearsNumber) {
		*this = DecreaseDateByXYearsFaster(*this, YearsNumber);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date) {
		Date.Year -= 10;
		return Date;
	}
	void DecreaseDateByOneDecade() {
		*this = DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate& Date, short DecadesNumber) {
		for (int i = 1; i <= DecadesNumber; i++) {
			Date = DecreaseDateByOneDecade(Date);
		}
		return Date;
	}
	void DecreaseDateByXDecades(short DecadesNumber) {
		*this = DecreaseDateByXDecades(*this, DecadesNumber);
	}

	static clsDate DecreaseDateByXDecadesFaster(clsDate& Date, short DecadesNumber) {
		Date.Year -= (DecadesNumber * 10);
		return Date;
	}
	void DecreaseDateByXDecadesFaster(short DecadesNumber) {
		*this = DecreaseDateByXDecadesFaster(*this, DecadesNumber);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date) {
		Date.Year -= 100;
		return Date;
	}
	void DecreaseDateByOneCentury() {
		*this = DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate& Date) {
		Date.Year -= 1000;
		return Date;
	}
	void DecreaseDateByOneMillennium() {
		*this = DecreaseDateByOneMillennium(*this);
	}

	static string GetSystemDateTimeString() {
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/"
			+ to_string(Year) + " - "
			+ to_string(Hour) + ":" + to_string(Minute)
			+ ":" + to_string(Second));
	}

	friend class clsInputValidate;
};

