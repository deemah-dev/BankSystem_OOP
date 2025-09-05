#pragma once
#include"clsScreen.h";
#include"clsUsers.h";
#include"clsDate.h";
class clsLoginRegisterListScreen : protected clsScreen {
	static void _PrintLoginRegisterRecord(clsUsers::strLoginRegisterInfo LoginInfo) {
		cout << "\t| " << setw(35) << left << LoginInfo.DateTime;
		cout << "| " << setw(25) << left << LoginInfo.sUsername;
		cout << "| " << setw(17) << left << LoginInfo.sPassword;
		cout << "| " << setw(12) << left << to_string(LoginInfo.sPermission);
	}
public:
	static void ShowLoginRegisterListScreen() {
		if (_CheckPermission(clsUsers::enMainMenuPermission::PShowLoginRegisterInfoScreen)) {
			return;
		}
		vector <clsUsers::strLoginRegisterInfo> vLoginInfo = clsUsers::GetLoginRegisterList();
		_PrintHeaderScreen("Login Register List Screen", to_string(vLoginInfo.size()) + " Record(s)");
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________________________\n" << endl;
		cout << "\t| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(25) << "Username";
		cout << "| " << left << setw(17) << "Password";
		cout << "| " << left << setw(12) << "Permission";
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________________________\n" << endl;
		if (vLoginInfo.size() == 0)
			cout << "\t\t\t\t\tNo Records Available\n";
		else {
			for (clsUsers::strLoginRegisterInfo I : vLoginInfo)
			{
				_PrintLoginRegisterRecord(I);
				cout << endl;
			}
			cout << "\n\t_______________________________________________________";
			cout << "_________________________________________________________\n" << endl;
		}
	}
};