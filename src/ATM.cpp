#include <iostream>
#include <fstream>
#include <limits>
#include <unordered_map>
#include <array>
#include <iomanip>
#include <ctime>
#include "../include/json.hpp"
#include "../include/ATM.hpp"

using json = nlohmann::json;
std::unordered_map<std::string, Account> account;

std::string hashPin(const std::string &inputPin) {
	std::hash <std::string> hasher;
    return std::to_string(hasher(inputPin));
}

void loadAccounts() {
    std::ifstream file("./accounts.json");
    if (!file.is_open()) return;

    json accounts;
    try {
        file >> accounts;
    } catch (const json::exception& error) {
        std::cerr << "Warning: accounts.json could not be read (" << error.what()
                  << "). Starting with an empty ledger." << std::endl;
        return;
    }
    if (!accounts.is_array()) return;

    for (const auto& anAccount : accounts) {
        try {
            const std::string username = anAccount.value("Username", "");
            const std::string name = anAccount.value("Account name", "");
            const std::string hashedPin = anAccount.value("User Pin", "");
            const std::string type = anAccount.value("Account type", "");
            const double balance = anAccount.value("Account balance", 0);
            const std::vector <std::string> transactionHistory = anAccount.value("Transaction History", std::vector <std::string>{});
            if(username.empty()) continue;
            account.emplace(username, Account(name, hashedPin, type, balance, transactionHistory));
        } catch (const json::exception&) {
            continue;
        }
    }
    file.close();
}

void saveAccounts() {
    std::ofstream file("./accounts.json");
	if (!file.is_open()) {
        std::cerr << "Error opening accounts.json" << std::endl;
        return;
    }
	
    json accountArray = json::array();
    for (auto& [username, acc] : account) {
        if (username != "Shadow as admin.") {
            json anAccount;

            anAccount["Username"] = username;
            anAccount["Account name"] = acc.getAcctName();
            anAccount["User Pin"] = acc.returnPin();
            anAccount["Account type"] = acc.getAccountType();
            anAccount["Account balance"] = acc.getAccountBalance();
			anAccount["Transaction History"] = acc.getTransactionHistory();
			
            accountArray.push_back(anAccount);
        }
    }
    file << std::setw(4) << accountArray << std::endl;
    file.close();
}

bool createAccount(const std::string& anAcctName, const std::string& username, const std::string& createPin) {
    if (account.find(username) != account.end() || username.empty()) {
        std::cout << "This username already exists. Please enter another username." << std::endl;
        return false;
    }
	std::string firstHistory = "Opened an account | Time ID: " + std::to_string(time(0));
	std::vector <std::string> openingHistory = {firstHistory};
    account.emplace(username, Account(anAcctName, hashPin(createPin), "savings", 0, openingHistory));
	
    saveAccounts();
    std::cout << "Account has been created successfully." << std::endl;
    return true;
}

std::string validateUser() {
    std::string uname = "";
    std::string inputPin = "";

    std::cout << "Enter your username: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, uname);

    if (account.find(uname) != account.end()) {
        std::cout << "Enter your four digit PIN: ";
        std::cin >> inputPin;

        if (account[uname].validatePin(inputPin)) return uname;

        std::cout << "Incorrect PIN entered for " << uname << "." << std::endl << std::endl;
        return "";
    }
    std::cerr << "Account does not exist." << std::endl << std::endl;
    return "";
}

std::string adminLogin() {
	std::string uname = "";
	std::string Pin = "";
    std::cout << "Enter your username: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, uname);
    if (uname != "Shadow as admin."){
		std::cout << "Invalid username" << std::endl;
		return "";
	}
    if (account.find("Shadow as admin.") != account.end()) {
        std::cout << "Enter your PIN: ";
        std::cin >> Pin;
        if (account["Shadow as admin."].validatePin(Pin)) return "Shadow as admin.";
        std::cout << "Incorrect PIN entered for admin Shadow." << std::endl << std::endl;
        return "";
    }
    std::cerr << "Account does not exist." << std::endl << std::endl;
    return "";
}

bool isValidPin(const std::string& pin) {
    if (pin.length() != 4) return false;
    for (char c : pin) if (!std::isdigit(c)) return false;
    return true;
}

double getValidAmount() {
    double amt;
    std::cin >> amt;
    if (std::cin.fail() || amt <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1; //invalid
    }
    return amt;
}

int getValidOption() {
    int opt;
    std::cin >> opt;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1; // invalid
    }
    return opt;
}