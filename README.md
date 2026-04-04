# cpp-CLI-VirtualBank
Virtual Bank of C++ (CLI Banking System)

A Command Line Interface (CLI) banking system built with modern C++ (OOP principles) and JSON-based persistence using nlohmann JSON.

This project simulates core banking operations such as account creation, deposits, withdrawals, transfers, and admin management — all within a structured, modular C++ architecture.

Features

- Account Creation with PIN authentication
- Deposit & Withdrawal system
- Secure fund transfers between users
- PIN hashing & validation
- Account types (Savings, Current, Fixed Deposit)
- Transaction history tracking
- Persistent storage using JSON
- Hidden Admin Mode (6789)
- Admin account deletion system
- Full account inspection (Admin)

Project Architecture (OOP Breakdown):

1. Account Class (Core Banking Logic)

Encapsulates all account-related data and operations.

Private Members (Encapsulation)
- std::string accountType
- std::string acctName
- std::string pin
- std::vector<std::string> transactionHistory
- double accountBalance

Key Methods
- deposit() -> Adds money + logs transaction
- withdraw() -> Deducts money with validation
- makeTransfer() -> Transfers between users
- resetPin() -> Secure PIN update
- setAccountType() -> Validates and updates type
- displayInfo() -> Prints full account details

Example (Deposit Logic):
bool Account::deposit(double amount) {
    if (amount > 0) {
        accountBalance += amount;
        transactionHistory.push_back("Deposit...");
        saveAccounts();
        return true;
    }
    return false;
}

Every financial action updates:
- Balance
- Transaction history
- JSON storage

2. Global Account Database

std::unordered_map<std::string, Account> account;

- Acts like a mini database
- Key = username
- Value = Account object

3. ATM Module (System Control Layer)

Handles:
- File I/O (JSON)
- Authentication
- Input validation
- System utilities

PIN Hashing:
std::string hashPin(const std::string &inputPin) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(inputPin));
}

JSON Persistence:
- loadAccounts() -> Reads from accounts.json
- saveAccounts() -> Writes to accounts.json

4. CLI Interface (main.cpp)

The engine of interaction:
- Menu-driven system
- Handles user flows
- Connects UI → Logic

Menu System:
1. Create Account
2. Transfer
3. Deposit
4. Withdraw
5. Change PIN
6. Check Info
7. Change Account Type
8. Exit

Hidden Admin Mode:
Enter: 6789

Admin can:
- View all users
- Delete accounts

Project Structure

VirtualBank v1.0.0/
│
├── include/
│   ├── account.hpp
│   ├── ATM.hpp
│   └── json.hpp
│
├── src/
│   ├── account.cpp
│   ├── ATM.cpp
│   └── main.cpp
│
├── accounts.json
├── compile.bat
└── README.md

Compilation Guide
-----------------

Compile from the project root directory.

MSVC (Windows):
cl /std:c++latest /EHsc /nologo /W4 /MTd src\account.cpp src\ATM.cpp src\main.cpp /Fe:VirtualBank.exe

g++ (Cross-Platform):

Windows (MinGW / g++):
g++ -std=c++20 src/account.cpp src/ATM.cpp src/main.cpp -Iinclude -o VirtualBank.exe

macOS:
g++ -std=c++20 src/account.cpp src/ATM.cpp src/main.cpp -Iinclude -o VirtualBank

Linux:
g++ -std=c++20 src/account.cpp src/ATM.cpp src/main.cpp -Iinclude -o VirtualBank

Quick Compile (All OS):

You can also use:
compile.bat

Important:
- On Windows -> double-click or run normally
- On Linux/macOS -> run with:
bash compile.bat

How It Works:

1. Program loads accounts from accounts.json
2. User interacts via CLI
3. Operations update:
   - Memory (unordered_map)
   - File (accounts.json)
4. Every transaction is logged with:
Amount + Timestamp (time ID)

Security Notes
--------------

- PINs are hashed (not stored as plain text)
- Basic validation ensures:
  - PIN = 4 digits
  - Valid transaction amounts
- Admin account is protected

Future Improvements:

- GUI version using QT
- Multi-threaded transactions for real-time concurrency.
- Account statement export to PDF.
- Support for multiple currencies.

Author: Gerald Chukwudera Mathew
	“The Programmer — Virtual Bank of C++”

License
-------

Copyright © Gerald Chukwudera Mathew
This project is under development and subject to updates.
