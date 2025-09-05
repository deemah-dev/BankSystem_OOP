#pragma once
#include<iostream>
#include<cstdlib>
#include<string>
using namespace std;
class clsUtility {
public:
	static void Srand() {
		srand((unsigned)time(NULL));
	}

	enum enNumberTypeP { Prime = 1, NotPrime = 2 };
	static enNumberTypeP ChickPrimeNumber(int num) {
		int HalfNumber = num / 2;
		for (int i = 2; i <= HalfNumber; i++) {
			if (num % i == 0)
				return enNumberTypeP::NotPrime;
		}
		return enNumberTypeP::Prime;
	}

	static int GetSumOfDigits(int num) {
		int Reminder = 0, sum = 0;
		while (num != 0) {
			Reminder = num % 10;
			num = num / 10;
			sum += Reminder;
		}
		return sum;
	}

	static int GetFrequency(int num, int digit) {
		int Reminder = 0, Freq = 0;
		while (num != 0) {
			Reminder = num % 10;
			num = num / 10;
			if (Reminder == digit) {
				Freq++;
			}
		}
		return Freq;
	}

	static int ReverseNumber(int num) {
		int Reminder = 0, NumberReversed = 0;
		while (num != 0) {
			Reminder = num % 10;
			num = num / 10;
			NumberReversed = Reminder + NumberReversed * 10;
		}
		return NumberReversed;

	}

	static bool CheckPalindromeNumber(int num) {
		return(num == ReverseNumber(num));
	}

	static string EncryptText(string Text, short EncryptionKey = 5) {
		for (int i = 0; i <= Text.length(); i++)
			Text[i] = char((int)Text[i] + EncryptionKey);
		return Text;
	}

	static string DecryptText(string Text, short EncryptionKey = 5) {
		for (int i = 0; i <= Text.length(); i++)
			Text[i] = char((int)Text[i] - EncryptionKey);
		return Text;
	}

	static int RandomNumber(int From, int To) {
		int RandNum = rand() % (To - From + 1) + From;
		return RandNum;
	}

	enum enCharacterType { SmallLetter = 1, CapitalLetter = 2, SpecialChar = 3, Digit = 4, All = 5 };
	static char GetRandomCharacter(enCharacterType CharacterType) {
		switch (CharacterType) {
		case enCharacterType::SmallLetter:
			return char(RandomNumber(97, 122));
		case enCharacterType::CapitalLetter:
			return char(RandomNumber(65, 90));
		case enCharacterType::SpecialChar:
			return char(RandomNumber(33, 47));
		case enCharacterType::Digit:
			return char(RandomNumber(48, 57));
		default:
			return char(RandomNumber(33, 122));
		}
	}

	static bool CheckPerfectNumber(int num) {
		int sum = 0;
		for (int i = 1; i < num; i++) {
			if (num % i == 0)
				sum += i;
		}
		return sum == num;
	}
private:
	static string GenerateWord(enCharacterType CharacterType, short Length) {
		string word;
		for (int i = 1; i <= Length; i++) {
			word = word + GetRandomCharacter(CharacterType);
		}
		return word;
	}
public:
	static string GenerateKey() {
		string FullKey;
		FullKey = GenerateWord(enCharacterType::CapitalLetter, 4) + "-";
		FullKey = FullKey + GenerateWord(enCharacterType::CapitalLetter, 4) + "-";
		FullKey = FullKey + GenerateWord(enCharacterType::CapitalLetter, 4) + "-";
		FullKey = FullKey + GenerateWord(enCharacterType::CapitalLetter, 4);
		return FullKey;

	}

	static void Swap2Numbers(int& num1, int& num2) {
		int ToSwap;
		ToSwap = num1;
		num1 = num2;
		num2 = ToSwap;
	}

	enum enNumberTypeEO { Even = 1, Odd = 2 };
	static enNumberTypeEO CheckNumberType(int num) {
		if (num % 2 != 0)
			return enNumberTypeEO::Odd;
		else
			return enNumberTypeEO::Even;
	}

	static string TextNumber(int num) {
		if (num == 0) {
			return "";
		}
		if (num >= 1 && num <= 19) {
			string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten",
				"Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };
			return arr[num] + " ";
		}
		if (num >= 20 && num <= 99) {
			string arr[] = { "", "", "Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
			return arr[num / 10] + " " + TextNumber(num % 10);
		}
		if (num >= 100 && num <= 199) {
			return "One Hundred " + TextNumber(num % 100);
		}
		if (num >= 200 && num <= 999) {
			return TextNumber(num / 100) + " Hundreds " + TextNumber(num % 100);
		}
		if (num >= 1000 && num <= 1999) {
			return "One Thousand " + TextNumber(num % 1000);
		}
		if (num >= 2000 && num <= 999999) {
			return TextNumber(num / 1000) + " Thousands " + TextNumber(num % 1000);
		}
		if (num >= 1000000 && num <= 1999999) {
			return "One Million " + TextNumber(num % 1000000);
		}
		if (num >= 2000000 && num <= 999999999) {
			return TextNumber(num / 1000000) + " Millions " + TextNumber(num % 1000000);
		}
		if (num >= 1000000000 && num <= 19999999999) {
			return "One Billion " + TextNumber(num % 1000000000);
		}
		else
			return TextNumber(num / 1000000000) + " Billions " + TextNumber(num % 1000000000);
	}
	static string Tab(short TabsNumb) {
		string tabs = "\t";
		for (int i = 1; i < TabsNumb; i++)
			tabs += "\t";
		return tabs;
	}
};


