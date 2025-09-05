#pragma once
#include"clsScreen.h";
#include"clsBankClient.h";
class clsTransferListScreen : protected clsScreen {
	static void _PrintTransferRecord(clsBankClient::strTransferInfo TransferInfo ) {
		cout << "\t| " << setw(25) << left << TransferInfo.DateTime;
		cout << "| " << setw(10) << left << TransferInfo.SCAccountNumber;
		cout << "| " << setw(10) << left << TransferInfo.DCAccountNumber;
		cout << "| " << setw(15) << left << TransferInfo.Amount;
		cout << "| " << setw(15) << left << TransferInfo.SBalance;
		cout << "| " << setw(15) << left << TransferInfo.DBalance;
		cout << "| " << setw(12) << left << TransferInfo.Username;
	}
public:
	static void ShowTransferListScreen() {
		vector <clsBankClient::strTransferInfo> vTransferInfo = clsBankClient::GetTransferLogList();
		_PrintHeaderScreen("Transfer Log List Screen", to_string(vTransferInfo.size()) + " Record(s)");
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________________________\n" << endl;
		cout << "\t| " << left << setw(25) << "Date/Time";
		cout << "| " << left << setw(10) << "SC.Acc";
		cout << "| " << left << setw(10) << "DC.Acc";
		cout << "| " << left << setw(15) << "Amount";
		cout << "| " << left << setw(15) << "S.Balance";
		cout << "| " << left << setw(15) << "D.Balance";
		cout << "| " << left << setw(12) << "User";
		cout << "\n\t_______________________________________________________";
		cout << "_________________________________________________________\n" << endl;
		if (vTransferInfo.size() == 0)
			cout << "\t\t\t\t\tNo Records Available\n";
		else {
			for (clsBankClient::strTransferInfo T : vTransferInfo)
			{
				_PrintTransferRecord(T);
				cout << endl;
			}
			cout << "\n\t_______________________________________________________";
			cout << "_________________________________________________________\n" << endl;
		}
	}
};

