#pragma once
#include<iostream>
#include<vector>
using namespace std;

class clsString {
private:
	string _Text = "";
	static char InvertChar(char Cr1) {
		return (isupper(Cr1) ? tolower(Cr1) : toupper(Cr1));
	}
	static bool IsVowel(char Cr1) {
		Cr1 = tolower(Cr1);
		return (Cr1 == 'a' || Cr1 == 'e' || Cr1 == 'i' || Cr1 == 'o' || Cr1 == 'u');
	}

public:
	clsString() {
		_Text = "";
	}

	clsString(string Text) {
		_Text = Text;
	}

	void SetText(string Text) {
		_Text = Text;
	}

	string GetText() {
		return _Text;
	}

	__declspec(property(get = GetText, put = SetText)) string Text;
	enum enLetterType { SmallLetters = 1, CapitalLetters = 2, All = 3 };

	static void PrintFirstLetters(string Str) {
		bool IsFirstChar = 1;
		for (int i = 0; i < Str.length(); i++) {
			if (IsFirstChar && Str[i] != ' ')
				cout << Str[i] << endl;
			IsFirstChar = (Str[i] == ' ' ? 1 : 0);
		}
	}
	void PrintFirstLetters() {
		PrintFirstLetters(_Text);
	}

	static string UpperFirstLetters(string Str) {
		bool IsFirstChar = 1;
		for (int i = 0; i < Str.length(); i++) {
			if (IsFirstChar && Str[i] != ' ') {
				Str[i] = toupper(Str[i]);
			}
			IsFirstChar = (Str[i] == ' ' ? 1 : 0);
		}
		return Str;
	}
	void UpperFirstLetters() {
		_Text = UpperFirstLetters(_Text);
	}

	static string LowerFirstLetters(string Str) {
		bool IsFirstChar = 1;
		for (int i = 0; i < Str.length(); i++) {
			if (IsFirstChar && Str[i] != ' ') {
				Str[i] = tolower(Str[i]);
			}
			IsFirstChar = (Str[i] == ' ' ? 1 : 0);
		}
		return Str;
	}
	void LowerFirstLetters() {
		_Text = LowerFirstLetters(_Text);
	}

	static string UpperAllLetters(string Str) {
		bool IsFirstChar = 1;
		for (int i = 0; i < Str.length(); i++) {
			Str[i] = toupper(Str[i]);
		}
		return Str;
	}
	void UpperAllLetters() {
		_Text = UpperAllLetters(_Text);
	}

	static string LowerAllLetters(string Str) {
		bool IsFirstChar = 1;
		for (int i = 0; i < Str.length(); i++) {
			Str[i] = tolower(Str[i]);
		}
		return Str;
	}
	void LowerAllLetters() {
		_Text = LowerAllLetters(_Text);
	}

	static string InvertAllLetters(string Str) {
		for (int i = 0; i < Str.length(); i++) {
			if (Str[i] != ' ')
				Str[i] = InvertChar(Str[i]);
		}
		return Str;
	}
	void InvertAllLetters() {
		_Text = InvertAllLetters(_Text);
	}

	static int CountLetters(string Str, enLetterType LetterType = enLetterType::All) {
		if (LetterType == enLetterType::All)
			return Str.length();
		short Counter = 0;
		for (short i = 0; i < Str.length(); i++) {
			if (Str[i] != ' ') {
				if (LetterType == enLetterType::SmallLetters && islower(Str[i]))
					Counter++;
				if (LetterType == enLetterType::CapitalLetters && isupper(Str[i]))
					Counter++;
			}
		}
		return Counter;
	}
	int CountLetters(enLetterType LetterType = enLetterType::All) {
		return CountLetters(_Text, LetterType);
	}

	static int CountSpecificLetter(string Str, char Cr1) {
		short counter = 0;
		for (short i = 0; i < Str.length(); i++) {
			if (Str[i] == Cr1)
				counter++;
		}
		return counter;
	}
	int CountSpecificLetter(char Cr1) {
		return CountSpecificLetter(_Text, Cr1);
	}

	static int CountLetterMachCase(string Str, char Cr1, bool IsMachCase = 1) {
		int counter = 0;
		for (int i = 0; i < Str.length(); i++) {
			if (IsMachCase) {
				if (Str[i] == Cr1)
					counter++;
			}
			else {
				if (tolower(Str[i]) == tolower(Cr1))
					counter++;
			}
		}
		return counter;
	}
	int CountLetterMachCase(char Cr1, bool IsMachCase = 1) {
		return CountLetterMachCase(_Text, Cr1, IsMachCase);
	}

	static int CountVowel(string Str) {
		short counter = 0;
		for (short i = 0; i < Str.length(); i++) {
			if (IsVowel(Str[i]))
				counter++;
		}
		return counter;
	}
	int CountVowel() {
		return CountVowel(_Text);
	}

	static void PrintVowel(string Str) {
		for (short i = 0; i < Str.length(); i++) {
			if (IsVowel(Str[i]))
				cout << Str[i] << "\t";
		}
	}
	void PrintVowel() {
		PrintVowel(_Text);
	}

	static void PrintEachWord(string S1) {
		string delim = " ";
		short Pos = 0;
		string word = "";
		while ((Pos = S1.find(delim)) != std::string::npos) {
			word = S1.substr(0, Pos);
			if (word != "") {
				cout << word << endl;
			}
			S1.erase(0, Pos + delim.length());
		}
		if (S1 != "")
			cout << S1 << endl;
	}
	void PrintEachWord() {
		PrintEachWord(_Text);
	}

	static int CountWords(string S1) {
		string delim = " ";
		short Pos = 0;
		string word = "";
		short counter = 0;
		while ((Pos = S1.find(delim)) != std::string::npos) {
			word = S1.substr(0, Pos);
			if (word != "") {
				counter++;
			}
			S1.erase(0, Pos + delim.length());
		}
		if (S1 != "")
			counter++;
		return counter;
	}
	int CountWords() {
		return CountWords(_Text);
	}

	static vector <string> Split(string Str, string Delim) {
		short Pos = 0;
		string word = "";
		vector <string> VWords;
		while ((Pos = Str.find(Delim)) != std::string::npos) {
			word = Str.substr(0, Pos);
			if (word != "") {
				VWords.push_back(word);
			}
			Str.erase(0, Pos + Delim.length());
		}
		if (Str != "")
			VWords.push_back(Str);

		return VWords;
	}
	vector <string> Split(string Delim) {
		return Split(_Text, Delim);
	}

	static string JoinString(vector <string> VWords, string Delim) {
		string S = "";
		for (string& s : VWords)
			S = S + s + Delim;
		return S.substr(0, S.length() - Delim.length());
	}
	static string JoinString(string Arr[], short ArrLength, string Delim) {
		string S = "";
		for (int i = 0; i < ArrLength; i++)
			S = S + Arr[i] + Delim;
		return S.substr(0, S.length() - Delim.length());
	}

	static string TrimLeft(string Str) {
		for (short i = 0; i < Str.length(); i++) {
			if (Str[i] != ' ')
				return Str.substr(i, Str.length() - i);
		}
		return "";
	}
	void TrimLeft() {
		_Text = TrimLeft(_Text);
	}

	static string TrimRight(string Str) {
		for (short i = Str.length() - 1; i >= 0; i--) {
			if (Str[i] != ' ')
				return Str.substr(0, i + 1);
		}
		return "";
	}
	void TrimRight() {
		_Text = TrimRight(_Text);
	}

	static string Trim(string Str) {
		return TrimLeft(TrimRight(Str));
	}
	void Trim() {
		_Text = Trim(_Text);
	}

	static string ReverseWords(string Str) {
		vector <string>VWords;
		string String;
		VWords = Split(Str, " ");
		vector<string>::iterator Iter = VWords.end();
		while (Iter != VWords.begin()) {
			Iter--;
			String = String + *Iter + " ";
		}
		String = String.substr(0, String.length() - 1);
		return String;
	}
	void ReverseWords() {
		_Text = ReverseWords(_Text);
	}

	static string ReplaceWord(string Str, string WordToReplace, string ReplaceTo, bool IsMachCase = 1) {
		vector <string> VStr = Split(Str, " ");
		for (string& s : VStr) {
			if (IsMachCase) {
				if (s == WordToReplace)
					s = ReplaceTo;
			}
			else {
				if (LowerAllLetters(s) == LowerAllLetters(WordToReplace))
					s = ReplaceTo;
			}
		}
		return JoinString(VStr, " ");
	}
	string ReplaceWord(string WordToReplace, string ReplaceTo, bool IsMachCase = 1) {
		return ReplaceWord(_Text, WordToReplace, ReplaceTo, IsMachCase);
	}

	static string RemovePunctuations(string Str) {
		string StrWithoutPunct = "";
		for (short i = 0; i < Str.length(); i++) {
			if (!ispunct(Str[i]))
				StrWithoutPunct += Str[i];
		}
		return StrWithoutPunct;
	}
	void RemovePunctuations() {
		_Text = RemovePunctuations(_Text);
	}

	void Print() {
		cout << _Text;
	}

};

