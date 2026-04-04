#pragma once
#include <string>
#include "./account.hpp"

extern std::unordered_map<std::string, Account> account;

std::string hashPin(const std::string &inputPin);
void loadAccounts();
void saveAccounts();
bool createAccount(const std::string& acctName, const std::string& username, const std::string& createPin);
std::string validateUser();
std::string adminLogin();
bool isValidPin(const std::string& pin);
double getValidAmount();
int getValidOption();