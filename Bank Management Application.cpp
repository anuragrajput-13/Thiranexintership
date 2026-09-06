#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class BankAccount {
private:
    int accountNo;
    string name;
    double balance;

public:
    // Create new account
    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accountNo;

        cin.ignore();

        cout << "Enter Customer Name: ";
        getline(cin, name);

        cout << "Enter Initial Balance: ";
        cin >> balance;

        cout << "\nAccount created successfully!\n";
    }

    // Display account details
    void displayAccount() {
        cout << "\n-----------------------------";
        cout << "\nAccount Number : " << accountNo;
        cout << "\nCustomer Name  : " << name;
        cout << "\nBalance        : Rs. " << balance;
        cout << "\n-----------------------------\n";
    }

    // Deposit money
    void deposit() {
        double amount;

        cout << "\nEnter amount to deposit: Rs. ";
        cin >> amount;

        if (amount > 0) {
            balance += amount;
            cout << "Amount deposited successfully!\n";
            cout << "New Balance: Rs. " << balance << endl;
        } else {
            cout << "Invalid amount!\n";
        }
    }

    // Withdraw money
    void withdraw() {
        double amount;

        cout << "\nEnter amount to withdraw: Rs. ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Invalid amount!\n";
        }
        else if (amount > balance) {
            cout << "Insufficient balance!\n";
        }
        else {
            balance -= amount;
            cout << "Amount withdrawn successfully!\n";
            cout << "Remaining Balance: Rs. " << balance << endl;
        }
    }

    // Check balance
    void checkBalance() {
        cout << "\nCurrent Balance: Rs. " << balance << endl;
    }

    int getAccountNo() {
        return accountNo;
    }
};

// Create account
void addAccount() {
    BankAccount account;

    ofstream file("bank.dat", ios::binary | ios::app);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    account.createAccount();

    file.write((char*)&account, sizeof(account));

    file.close();
}

// Display all accounts
void displayAccounts() {
    BankAccount account;

    ifstream file("bank.dat", ios::binary);

    if (!file) {
        cout << "\nNo accounts found!\n";
        return;
    }

    bool found = false;

    while (file.read((char*)&account, sizeof(account))) {
        account.displayAccount();
        found = true;
    }

    file.close();

    if (!found) {
        cout << "\nNo accounts found!\n";
    }
}

// Main function
int main() {

    int choice;

    do {
        cout << "\n====================================";
        cout << "\n       BANK MANAGEMENT SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Create Account";
        cout << "\n2. Display All Accounts";
        cout << "\n3. Exit";
        cout << "\n====================================";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            addAccount();
            break;

        case 2:
            displayAccounts();
            break;

        case 3:
            cout << "\nThank you for using Bank Management System!\n";
            break;

        default:
            cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 3);

    return 0;
}
