#pragma once
#include"clsScreen.h";
#include"clsBankClient.h";
#include"Global.h";
class clsClientsListScreen : public clsScreen{
	static void _PrintClientRecord(clsBankClient Client) {
		cout << "\t| " << setw(12) << left << Client.AccountNumber();
		cout << "| " << setw(12) << left << Client.PINCode;
		cout << "| " << setw(25) << left << Client.FullName();
		cout << "| " << setw(15) << left << Client.Phone;
		cout << "| " << setw(20) << left << Client.Email;
		cout << "| " << setw(12) << left << to_string(Client.AccountBalance);
	}
public:
	static void ShowClientsList() {
		if (_CheckPermission(clsUsers::enMainMenuPermission::PShowClients)) {
			return;
		}
		vector <clsBankClient> vClientsData = clsBankClient::GetClientsList();
		_PrintHeaderScreen("Clients List Screen", to_string(vClientsData.size()) + " Client(s)");
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________________________\n" << endl;
		cout << "\t| " << left << setw(12) << "Acc. Number";
		cout << "| " << left << setw(12) << "PIN Code";
		cout << "| " << left << setw(25) << "Full Name";
		cout << "| " << left << setw(15) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(12) << "Balance";
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________________________\n" << endl;
		if (vClientsData.size() == 0)
			cout << "\t\t\t\t\tNo Clients Available\n";
		else {
			for (clsBankClient C : vClientsData)
			{
				_PrintClientRecord(C);
				cout << endl;
			}
			cout << "\n\t_______________________________________________________";
			cout << "_________________________________________________________\n" << endl;
		}
	}
};