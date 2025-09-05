#pragma once
#include"clsPerson.h";
#include<fstream>
#include<string>
#include"clsString.h";
#include"clsUtility.h";
#include"clsDate.h";
#include"clsBankClient.h";
class clsUsers : public clsPerson {
private:
	string _Username;
	string _Password;
	short _Permission = 0;
	bool _Mark = 0;
	enum enMode { EmptyMode = 1, UpdateMode = 2, AddNewMode = 3 };
	enMode _Mode;
public:
	struct strLoginRegisterInfo {
		string DateTime;
		string sUsername;
		string sPassword;
		short sPermission = 0;
	};
private:
	static clsUsers _ConvertLineToUserObject(string Line) {
		vector <string> vUsersData;
		vUsersData = clsString::Split(Line, "#//#");
		return clsUsers(enMode::UpdateMode, vUsersData[0], vUsersData[1], vUsersData[2], vUsersData[3], vUsersData[4],clsUtility::DecryptText(vUsersData[5]), stoi(vUsersData[6]));
	}
	static strLoginRegisterInfo _ConvertLineToLoginRegisterInfo(string Line) {
		strLoginRegisterInfo LoginInfo;
		vector <string> vLoginInfo;
		vLoginInfo = clsString::Split(Line, "#//#");
		LoginInfo.DateTime = vLoginInfo[0];
		LoginInfo.sUsername += vLoginInfo[1];
		LoginInfo.sPassword += clsUtility::DecryptText(vLoginInfo[2]);
		LoginInfo.sPermission += stoi(vLoginInfo[3]);
		return LoginInfo;
	}
	static clsUsers _GetEmptyUserObject() {
		return clsUsers(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	static vector <clsUsers> _LoudUsersDataFromFile() {
		fstream File;
		vector <clsUsers> vUsersData;
		File.open("UsersData.txt", ios::in);
		if (File.is_open()) {
			string Line;
			while (getline(File, Line)) {
				clsUsers User = _ConvertLineToUserObject(Line);
				vUsersData.push_back(User);
			}
			File.close();
		}
		return vUsersData;
	}
	static vector <strLoginRegisterInfo> _LoudLoginInfoFromFile() {
		fstream File;
		vector <strLoginRegisterInfo> vLoginInfo;
		File.open("Log.txt", ios::in);
		if (File.is_open()) {
			string Line;
			while (getline(File, Line)) {
				strLoginRegisterInfo LoginInfo = _ConvertLineToLoginRegisterInfo(Line);
				vLoginInfo.push_back(LoginInfo);
			}
			File.close();
		}
		return vLoginInfo;
	}
	static string _ConvertUserObjectToLine(clsUsers User, string Delim = "#//#") {
		string UsersDataLine;
		UsersDataLine = User.FirstName + Delim;
		UsersDataLine += User.LastName + Delim;
		UsersDataLine += User.Email + Delim;
		UsersDataLine += User.Phone + Delim;
		UsersDataLine += User.Username + Delim;
		UsersDataLine += clsUtility::EncryptText(User.Password) + Delim;
		UsersDataLine += to_string(User.Permissions);
		return UsersDataLine;
	}
	static void _SaveUsersDataToFile(vector <clsUsers> vUsersData){
		fstream File;
		File.open("UsersData.txt", ios::out);
		if (File.is_open()) {
			string Line;
			for(clsUsers U : vUsersData) {
				if (!U._Mark) {
					Line = _ConvertUserObjectToLine(U);
					File << Line << endl;
				}
			}
			File.close();
		}
	}
	void _Update() {
		vector <clsUsers> _vUsersData;
		_vUsersData = _LoudUsersDataFromFile();
		for (clsUsers& U : _vUsersData) {
			if (U.Username == _Username) {
				U = *this;
				break;
			}
		}
		_SaveUsersDataToFile(_vUsersData);

	}
	void AddDataLineToFile(string Line) {
		fstream File;
		File.open("UsersData.txt", ios::out | ios::app);
		if (File.is_open()) {
			File << Line << endl;
			File.close();
		}
	}
	void _AddNew() {
		AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}
	void _MarkUsername(clsUsers User, vector <clsUsers>& vUsersData) {
		for (clsUsers& U : vUsersData) {
			if (U.Username == _Username) {
				U._Mark = 1; 
				break;
			}
		}
	}
	static string _ConvertUserLogInfoToLine(clsUsers User, string Delim = "#//#") {
		string UsersDataLine = "";
		clsDate Date;
		UsersDataLine += clsDate::GetSystemDateTimeString() + Delim;
		UsersDataLine += User.Username + Delim;
		UsersDataLine += clsUtility::EncryptText(User.Password) + Delim;
		UsersDataLine += to_string(User.Permissions);
		return UsersDataLine;
	}

public:
	enum enMainMenuPermission { PFullAccess = -1, PShowClients = 1, PAddClient = 2, PDeleteClient = 4, PUpdateClient = 8, PFindClient = 16, PTransactions = 32, PManageUsers = 64, PShowLoginRegisterInfoScreen = 128 };

	clsUsers(enMode Mode, string FirstName, string LastName, string Email, string Phone, string Username, string Password, short Permission) : clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_Username = Username;
		_Password = Password;
		_Permission = Permission;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	void SetUsername(string Username) {
		_Username = Username;
	}
	string GetUsername() {
		return _Username;
	}
	__declspec(property(get = GetUsername, put = SetUsername)) string Username;

	void SetPassword(string Password) {
		_Password = Password;
	}
	string GetPassword() {
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(short Permission) {
		_Permission = Permission;
	}
	short GetPermissions() {
		return _Permission;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) short Permissions;

	static clsUsers Find(string Username) {
		fstream File;
		File.open("UsersData.txt", ios::in);
		if (File.is_open()) {
			string Line;
			while (getline(File, Line)) {
				clsUsers User = _ConvertLineToUserObject(Line);
				if (Username == User.Username) {
					File.close();
					return User;
				}
			}
			File.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUsers Find(string Username, string Password) {
		fstream File;
		File.open("UsersData.txt", ios::in);
		if (File.is_open()) {
			string Line;
			while (getline(File, Line)) {
				clsUsers User = _ConvertLineToUserObject(Line);
				if (Username == User.Username && Password == User.Password) {
					File.close();
					return User;
				}
			}
			File.close();
		}
		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string Username) {
		clsUsers User = clsUsers::Find(Username);
		return (!User.IsEmpty());
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
			if (IsUserExist(Username))
				return enSave::SvFailed_Exist;
			else {
				_AddNew();
				return enSave::SvSucceeded;
			}
		}
	}

	static clsUsers AddNewUsername(string Username) {
		return clsUsers(enMode::AddNewMode, "", "", "", "", Username, "", 0);
	}

	bool Delete() {
		if (IsUserExist(Username)) {
			vector <clsUsers> vUsersData;
			vUsersData = _LoudUsersDataFromFile();
			_MarkUsername(*this, vUsersData);
			_SaveUsersDataToFile(vUsersData);
			*this = _GetEmptyUserObject();
			vUsersData = _LoudUsersDataFromFile();
			return 1;
		}
		else
			return 0;
	}

	static vector<clsUsers> GetUsersList() {
		return _LoudUsersDataFromFile();
	}

	static vector<strLoginRegisterInfo> GetLoginRegisterList() {
		return _LoudLoginInfoFromFile();
	}

	bool CheckPermission(enMainMenuPermission Permission) {
		if (this->Permissions == enMainMenuPermission::PFullAccess)
			return 1;
		if ((this->Permissions & Permission) == Permission)
			return 1;
		else
			return 0;
	}

	void SaveCurrentUserLogInfoToFile() {
		fstream File;
		string Line = _ConvertUserLogInfoToLine(*this);
		File.open("Log.txt", ios::out | ios::app);
		if (File.is_open()) {
			File << Line << endl;
			File.close();
		}
	}

};