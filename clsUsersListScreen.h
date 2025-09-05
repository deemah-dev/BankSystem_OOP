#pragma once
#include"clsScreen.h";
#include"clsUsers.h";
class clsUsersListScreen : public clsScreen {
	static void _PrintUserRecord(clsUsers User) {
		cout << "\t| " << setw(12) << left << User.Username;
		cout << "| " << setw(25) << left << User.FullName();
		cout << "| " << setw(15) << left << User.Phone;
		cout << "| " << setw(20) << left << User.Email;
		cout << "| " << setw(12) << left << User.Password;
		cout << "| " << setw(12) << left << to_string(User.Permissions);
	}
public:
	static void ShowUsersList() {
		vector <clsUsers> vUsersData = clsUsers::GetUsersList();
		_PrintHeaderScreen("Users List Screen", to_string(vUsersData.size()) + " User(s)");
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________________________\n" << endl;
		cout << "\t| " << left << setw(12) << "Username";
		cout << "| " << left << setw(25) << "Full Name";
		cout << "| " << left << setw(15) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(12) << "Password";
		cout << "| " << left << setw(12) << "Permission";
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________________________\n" << endl;
		if (vUsersData.size() == 0)
			cout << "\t\t\t\t\tNo Users Available\n";
		else {
			for (clsUsers C : vUsersData)
			{
				_PrintUserRecord(C);
				cout << endl;
			}
			cout << "\n\t_______________________________________________________";
			cout << "_________________________________________________________\n" << endl;
		}
	}
};