#pragma once
#include<string>
#include<vector>
#include<unordered_map>

class Account;
extern std::unordered_map<std::string, Account> account;
std::string hashPin(const std::string &inputPin);

class Account {

private:
	//Encapsulation of attributes
	std::string accountType = "savings";
    std::string acctName = "No Name";
    std::string pin = hashPin("0000");
    std::vector <std::string> transactionHistory;
	double accountBalance = 0;

public:
	//Class initializations
	Account(const std::string& name, const std::string& p, const std::string& type, double balance, const std::vector<std::string> &aTransactionHistory);
    Account(const std::string& anAcctName);
	Account();
    
    //Accessors
    std::string getAcctName() const;
    std::string returnPin() const;
    double getAccountBalance() const;
    std::string getAccountType() const;
	std::vector<std::string> getTransactionHistory() const;

	//Class Methods
    void displayAccountBalance() const;
    bool deposit(double amount);
    bool withdraw(double amount);
    bool resetPin(const std::string& oldPin, const std::string& newPin);
    void displayInfo() const;
    bool setAccountType(const std::string anAccountType);
    bool makeTransfer(const std::string& user2, double amount);
    bool validatePin(std::string Pin) const;
};
