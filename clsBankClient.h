#pragma once
#include"clsPerson.h";
#include<fstream>
#include<string>
#include"clsString.h";
#include"clsUtility.h";
class clsBankClient : public clsPerson {
private:
	string _AccountNumber;
	string _PINCode;
	double _AccountBalance = 0;
	bool _Mark = 0;
	enum enMode { EmptyMode = 1, UpdateMode = 2, AddNewMode = 3 };
	enMode _Mode;
public:
	struct strTransferInfo {
		string DateTime;
		string SCAccountNumber;
		string DCAccountNumber;
		double Amount = 0;
		double SBalance = 0;
		double DBalance = 0;
		string Username;
	};
private:
	static clsBankClient _ConvertLineToClientObject(string Line) {
		vector <string> vClientsData;
		vClientsData = clsString::Split(Line, "#//#");
		return clsBankClient(enMode::UpdateMode, vClientsData[0], vClientsData[1], vClientsData[2], vClientsData[3], vClientsData[4], vClientsData[5], stod(vClientsData[6]));
	}
	static strTransferInfo _ConvertLineToTransferRecord(string Line) {
		strTransferInfo TransferInfo;
		vector <string> vTransferLog;
		vTransferLog = clsString::Split(Line, "#//#");
		TransferInfo.DateTime = vTransferLog[0];
		TransferInfo.SCAccountNumber += vTransferLog[1];
		TransferInfo.DCAccountNumber += vTransferLog[2];
		TransferInfo.Amount += stod(vTransferLog[3]);
		TransferInfo.SBalance += stod(vTransferLog[4]);
		TransferInfo.DBalance += stod(vTransferLog[5]);
		TransferInfo.Username += vTransferLog[6];
		return TransferInfo;
	}
	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	static vector <clsBankClient> _LoudClientsDataFromFile() {
		fstream File;
		vector <clsBankClient> vClientsData;
		File.open("ClientsData.txt", ios::in);
		if (File.is_open()) {
			string Line;
			while (getline(File, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClientsData.push_back(Client);
			}
			File.close();
		}
		return vClientsData;
	}
	static string _ConvertClientObjectToLine(clsBankClient Client, string Delim = "#//#") {
		string ClientsDataLine;
		ClientsDataLine = Client.FirstName + Delim;
		ClientsDataLine += Client.LastName + Delim;
		ClientsDataLine += Client.Email + Delim;
		ClientsDataLine += Client.Phone + Delim;
		ClientsDataLine += Client.AccountNumber() + Delim;
		ClientsDataLine += Client.PINCode + Delim;
		ClientsDataLine += to_string(Client.AccountBalance);
		return ClientsDataLine;
	}
	static void _SaveClientsDataToFile(vector <clsBankClient> vClientsData) {
		fstream File;
		File.open("ClientsData.txt", ios::out);
		if (File.is_open()) {
			string Line;
			for(clsBankClient C : vClientsData) {
				if (!C._Mark) {
					Line = _ConvertClientObjectToLine(C);
					File << Line << endl;
				}
			}
			File.close();
		}
	}
	void _Update() {
		vector <clsBankClient> _vClientsData;
		_vClientsData = _LoudClientsDataFromFile();
		for (clsBankClient& C : _vClientsData) {
			if (C.AccountNumber() == _AccountNumber) {
				C = *this;
				break;
			}
		}
		_SaveClientsDataToFile(_vClientsData);

	}
	void AddDataLineToFile(string Line) {
		fstream File;
		File.open("ClientsData.txt", ios::out | ios::app);
		if (File.is_open()) {
			File << Line << endl;
			File.close();
		}
	}
	void _AddNew() {
		AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}
	void _MarkAccountNumber(clsBankClient Client, vector <clsBankClient>& vClientsData) {
		for (clsBankClient& C : vClientsData) {
			if (C.AccountNumber() == _AccountNumber) {
				C._Mark = 1; 
				break;
			}
		}
	}
	static string _ConvertTransferInfoToLine(clsBankClient SourceClient, clsBankClient DestinationClient, double Amount, string Username, string Delim = "#//#") {
		string TransferInfoLine = "";
		clsDate Date;
		TransferInfoLine += clsDate::GetSystemDateTimeString() + Delim;
		TransferInfoLine += SourceClient.AccountNumber() + Delim;
		TransferInfoLine += DestinationClient.AccountNumber() + Delim;
		TransferInfoLine += to_string(Amount) + Delim;
		TransferInfoLine += to_string(SourceClient.AccountBalance) + Delim;
		TransferInfoLine += to_string(DestinationClient.AccountBalance) + Delim;
		TransferInfoLine += Username;
		return TransferInfoLine;
	}
	static vector <strTransferInfo> _LoudTransferLogFromFile() {
		fstream File;
		vector <strTransferInfo> vTransferInfo;
		File.open("TransferLog.txt", ios::in);
		if (File.is_open()) {
			string Line;
			while (getline(File, Line)) {
				strTransferInfo TransferInfo  = _ConvertLineToTransferRecord(Line);
				vTransferInfo.push_back(TransferInfo);
			}
			File.close();
		}
		return vTransferInfo;
	}

public:
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PINCode, double AccountBalance) : clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PINCode = PINCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber() {
		return _AccountNumber;
	}

	void SetPINCode(string PINCode) {
		_PINCode = PINCode;
	}
	string GetPINCode() {
		return _PINCode;
	}
	__declspec(property(get = GetPINCode, put = SetPINCode)) string PINCode;

	void SetAccountBalance(double AccountBalance) {
		_AccountBalance = AccountBalance;
	}
	double GetAccountBalance() {
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

	static clsBankClient Find(string AccountNumber) {
		fstream File;
		File.open("ClientsData.txt", ios::in);
		if (File.is_open()) {
			string Line;
			while (getline(File, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (AccountNumber == Client._AccountNumber) {
					File.close();
					return Client;
				}
			}
			File.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PINCode) {
		fstream File;
		File.open("ClientsData.txt", ios::in);
		if (File.is_open()) {
			string Line;
			while (getline(File, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (AccountNumber == Client._AccountNumber && PINCode == Client._PINCode) {
					File.close();
					return Client;
				}
			}
			File.close();
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber) {
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	enum enSave{SvSucceeded = 1, SvFailed_Empty = 2, SvFailed_Exist};
	enSave Save() {
		switch (_Mode) {
		case enMode::EmptyMode:
			if(IsEmpty())
				return  enSave::SvFailed_Empty;
		case enMode::UpdateMode:
			_Update();
			return enSave::SvSucceeded;
		case enMode::AddNewMode:
			if (IsClientExist(_AccountNumber))
				return enSave::SvFailed_Exist;
			else {
				_AddNew();
				return enSave::SvSucceeded;
			}
		}
	}

	static clsBankClient AddNewAccountNumber(string AccountNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete() {
		if (IsClientExist(_AccountNumber)) {
			vector <clsBankClient> vClientsData;
			vClientsData = _LoudClientsDataFromFile();
			_MarkAccountNumber(*this, vClientsData);
			_SaveClientsDataToFile(vClientsData);
			*this = _GetEmptyClientObject();
			vClientsData = _LoudClientsDataFromFile();
			return 1;
		}
		else
			return 0;
	}

	static vector<clsBankClient> GetClientsList() {
		return _LoudClientsDataFromFile();
	}

	static double GetTotalBalances() {
		double TotalBalances = 0;
		vector <clsBankClient> vClientsData = _LoudClientsDataFromFile();
		for (clsBankClient& C : vClientsData) {
			TotalBalances += C.AccountBalance;
		}
		return TotalBalances;
	}

	void Deposit(double Amount) {
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount) {
		if (Amount > _AccountBalance) {
			return 0;
		}
		else {
			_AccountBalance -= Amount;
			Save();
			return 1;
		}
	}

	void SaveTransferLogToFile(clsBankClient DestinationClient, double Amount, string Username) {
		fstream File;
		string Line = _ConvertTransferInfoToLine(*this, DestinationClient, Amount, Username);
		File.open("TransferLog.txt", ios::out | ios::app);
		if (File.is_open()) {
			File << Line << endl;
			File.close();
		}
	}

	void Transfer(clsBankClient& DestinationClient, double Amount, string Username) {
		_AccountBalance -= Amount;
		DestinationClient.Deposit(Amount);
		SaveTransferLogToFile(DestinationClient, Amount, Username);
		Save();
	}

	static vector<strTransferInfo> GetTransferLogList() {
		return _LoudTransferLogFromFile();
	}

};