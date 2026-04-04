#include <iostream>
#include <cctype>
#include <iomanip>
#include <string>
#include <ctime>
#include "../include/account.hpp"
#include "../include/ATM.hpp"

extern std::unordered_map<std::string, Account> account;

Account::Account(const std::string& name, const std::string& p, const std::string& type, double balance, const std::vector<std::string> &aTransactionHistory) : accountType(type), acctName(name), pin(p), transactionHistory(aTransactionHistory), accountBalance(balance) {}
Account::Account(const std::string& anAcctName) : acctName(anAcctName) {}
Account::Account() : Account("No Name", hashPin("1234"), "savings", 0, std::vector <std::string> {}) {}
std::string Account::getAcctName() const { return acctName; }
std::string Account::returnPin() const { return pin; }
std::string Account::getAccountType() const { return accountType; }
double Account::getAccountBalance() const { return accountBalance; }
std::vector<std::string> Account::getTransactionHistory() const{return transactionHistory;}
void Account::displayAccountBalance() const {
        std::cout << "Dear " << acctName << ", your account balance is: $" << std::fixed << std::setprecision(2) << accountBalance << std::endl;
}

bool Account::deposit(double amount) {
    if (amount > 0) {
        accountBalance += amount;
		std::string history = "Deposit of $" + std::to_string(amount) + " | Time ID: " + std::to_string(time(0));
		transactionHistory.push_back(history);
        saveAccounts();
        return true;
    }
    return false;
}
bool Account::withdraw(double amount) {
    if (amount <= 0) {
        std::cerr << "Invalid amount." << std::endl;
        return false;
    }
    if (accountBalance >= amount) {
        accountBalance -= amount;
		std::string history = "Withdrawal of $" + std::to_string(amount) + " | Time ID: " + std::to_string(time(0));
		transactionHistory.push_back(history);
        saveAccounts();
		std::cout << "Withdrawal of $" << amount << " was successful" << std::endl;
        return true;
    }
    else {
        std::cout << "Insufficient funds." << std::endl;
        return false;
    }
}
bool Account::resetPin(const std::string& oldPin, const std::string& newPin) {
    if (hashPin(oldPin) != pin) return false;
    if (newPin.length() != 4) return false;
    for (char c : newPin) {
        if (!std::isdigit(c)) return false;
    }
    pin = hashPin(newPin);
    saveAccounts();
    return true;
}
void Account::displayInfo() const {
    std::cout << "\nAccount Name: " << acctName << std::endl;
    std::cout << "Account Type: " << accountType << std::endl;
    std::cout << "Account Balance: $" << std::fixed << std::setprecision(2) << accountBalance << std::endl;
	std::cout << "Transaction History:" << std::endl;
	for(const auto& transaction: transactionHistory){
	   std::cout << "- " << transaction << std::endl;
   }
}
bool Account::setAccountType(std::string anAccountType) {
    for (char& c : anAccountType){
		c = static_cast<char>(std::tolower(c));
		}
    if (anAccountType == "savings" || anAccountType == "current" || anAccountType == "fixed deposit") {
        accountType = anAccountType;
		std::string setAccountHistory = "Set account type to " + anAccountType + " | Time ID: " + std::to_string(time(0));
		transactionHistory.push_back(setAccountHistory);
        saveAccounts();
        return true;
    }
    return false;
}
bool Account::makeTransfer(const std::string& user2, double amount) {
    if (account.find(user2) == account.end()) {
		std::cerr << "Destination account does not exist." << std::endl;
        return false;
	}
	if(amount <= 0){
		std::cerr << "Invalid amount." << std::endl;
		return false;
	}
	if(accountBalance < amount){
		std::cout << "Insufficient funds." << std::endl;
		return false;
	}
	accountBalance -= amount;
	account[user2].deposit(amount);
	std::string history = "Transfer of $" + std::to_string(amount) + " to " + user2 + " | Time ID: " + std::to_string(time(0));
	transactionHistory.push_back(history);
	saveAccounts();
	std::cout << "Transfer of $" << std::fixed << std::setprecision(2) << amount << " to " << user2 << " was successful." << std::endl;
	return true;
}
bool Account::validatePin(std::string inputPin) const { return hashPin(inputPin) == pin; }