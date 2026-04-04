#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "../include/account.hpp"
#include "../include/ATM.hpp"
using namespace std;

extern unordered_map<string, Account> account;

int main() {
    account.emplace("Shadow as admin.", Account("The Programmer, Virtual Bank OF C++", hashPin("Kamar-Taj"), "Admin", 0.0, std::vector<std::string> {}));
    loadAccounts();
    while (true) {
        cout << "Welcome to Virtual Bank of C++\n"
            << "1. Create Account\n2. Transfer\n3. Deposit Money\n4. Withdraw Cash\n"
            << "5. Change PIN\n6. Check Account Info\n7. Change Account Type\n8. Exit\n";
        cout << "Choose an option: ";

        int option = getValidOption();
        if ((option < 1 || option > 8) && option != 6789) {
            cout << "Invalid option. Try again!" << endl << endl;
            continue;
        }

        string uname, inputPin;

        if (option == 1) {
            string name;
            cout << "Enter your account name: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);

            cout << "Enter your unique username: ";
            getline(cin, uname);

            cout << "Set your four digit PIN: ";
            cin >> inputPin;
            if (!isValidPin(inputPin)) {
                cout << "Invalid PIN format. Must be 4 digits." << endl<< endl;
				continue;
            }
            createAccount(name, uname, inputPin);
        }

        else if (option == 2) {
            uname = validateUser();
			if (uname.empty()) continue;
			cout << "Enter destination account: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			string destination;
			getline(cin, destination);

			cout << "Enter amount: ";
			double amount = getValidAmount();
			account[uname].makeTransfer(destination, amount);
        }

        else if (option == 3) {
            uname = validateUser();
			if (uname.empty()) continue;
            cout << "Enter amount to deposit: ";
            double amount = getValidAmount();
            if (account[uname].deposit(amount)){
                cout << "Your deposit of $" << fixed << setprecision(2) << amount << " was successful." << endl;
			}
            else
                cout << "Invalid amount entered." << endl;
        }

        else if (option == 4) {
            uname = validateUser();
			if (uname.empty()) continue;

            cout << "Enter amount to withdraw: ";
            double amount = getValidAmount();
            account[uname].withdraw(amount);
        }

        else if (option == 5) {
            uname = validateUser();
			if (uname.empty()) continue;
			cout << "Enter old pin: ";
			cin >> inputPin;
            cout << "Enter new four digit PIN: ";
            string uPin;
            cin >> uPin;
            if (!isValidPin(uPin)) {
                cout << "Invalid PIN format." << endl;
                continue;
            }

            if (account[uname].resetPin(inputPin, uPin))
                cout << "PIN reset was successful." << endl;
            else
                cout << "PIN reset failed." << endl;
        }

        else if (option == 6) {
            uname = validateUser();
			if (uname.empty()) continue;
			else account[uname].displayInfo();
        }

        else if (option == 7) {
            uname = validateUser();
			if (uname.empty()) continue;
            cout << "Enter the account type you wish to change to (savings, current, fixed deposit): ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string aType;
            getline(cin, aType);

            if (account[uname].setAccountType(aType))
                cout << "Account type updated to " << aType << " successfully." << endl;
            else
                cout << "Invalid account type entered." << endl;
        }

        else if (option == 8) {
            break;
        }
        else if (option == 6789) {
            cout << "Special Admin Login...\n";
			uname = adminLogin();
			if (uname.empty()) continue;
			char runAgain {};
			do {
				cout << "\n1. Show users' account info" << "\n2. Delete account\nSelect an option: ";
				int anOption{};
				cin >> anOption;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cerr << "Invalid input";
					continue;
				}
				if (anOption == 1) {
					bool hasUsers = false;
					for (const auto& [username, acc] : account) {
						if (username != "Shadow as admin.") {
							hasUsers = true;
							cout << "\nUsername: " << username;
							acc.displayInfo();
						}
					}
					if(!hasUsers)
						cerr << "No users found in the database" << endl;
				}
				else if (anOption == 2) {
					string user = "";
					cout << "Enter the username of the account you wish to delete: ";
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					getline(cin, user);
					if (account.find(user) != account.end() && user != "Shadow as admin.") {
						account.erase(user);
						saveAccounts();
						cout << "User " << user << " has been deleted successfully" << endl;
					}
					else {
						cout << "The specified user does not exist" << endl;
					}
				}
				else {
					cerr << "Invalid option selected" << endl;
					continue;
				}
				cout << "\nDo you want to perform another operation? (y/n): ";
				cin >> runAgain;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					runAgain = 'n';
				}
				else runAgain = static_cast<char>(tolower(runAgain));
			}
			while (runAgain == 'y');
        }
        cout << endl;
    }
	cout << "Thank you for using Virtual Bank of C++. Have a great day!" << endl;
	//Allow user see message before terminating the program
	this_thread::sleep_for(chrono::seconds(1));
    return 0;
}
