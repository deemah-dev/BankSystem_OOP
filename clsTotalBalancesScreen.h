#pragma once
#include"clsScreen.h";
#include"clsBankClient.h";
class clsTotalBalancesScreen : protected clsScreen {
	static void PrintClientBalances(clsBankClient Client) {
		cout << clsUtility::Tab(4) << "  | " << setw(12) << left << Client.AccountNumber();
		cout << "| " << setw(25) << left << Client.FullName();
		cout << "| " << setw(12) << left << to_string(Client.AccountBalance);
	}
public:
	static void ShowBalancesList() {
		vector <clsBankClient> vClientsData = clsBankClient::GetClientsList();
		_PrintHeaderScreen("Balances Screen", to_string(vClientsData.size()) + " Client(s)");

		cout << endl << clsUtility::Tab(2) << "  ____________________________________________________________________________";
		cout << "_______\n" << endl;
		cout << clsUtility::Tab(4) << "  | " << left << setw(12) << "Acc. Number";
		cout << "| " << left << setw(25) << "Full Name";
		cout << "| " << left << setw(12) << "Balance";
		cout<<endl << clsUtility::Tab(2) << "  ____________________________________________________________________________";
		cout << "_______\n" << endl;
		if (vClientsData.size() == 0)
			cout << "\t\tNo Clients Available\n";
		else {
			for (clsBankClient C : vClientsData)
			{
				PrintClientBalances(C);
				cout << endl;
			}
			cout <<endl<< clsUtility::Tab(2) << "  ____________________________________________________________________________";
			cout << "_______\n" << endl;
		}
		cout << clsUtility::Tab(2) << "  Total Balances : " << to_string(clsBankClient::GetTotalBalances()) << endl;
		cout << clsUtility::Tab(2) << "  Text Of Total Balances : " << clsUtility::TextNumber(clsBankClient::GetTotalBalances()) << endl;
	}
};
