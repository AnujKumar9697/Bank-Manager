#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <map>
#include <set>
#include <unordered_map>

using namespace std;

// Account class
class Account
{

private:
   int accountNumber;
   string holderName;
   double balance;

public:
   Account() : accountNumber(0), holderName(""), balance(0.0) {}

   Account(int accNo, const string &name, double initialBalance)
   {

      this->accountNumber = accNo;
      this->holderName = name;
      this->balance = initialBalance;
   }

   void deposit(double amount)
   {
      balance += amount;
      cout << " Deposited ₹" << amount << " successfully.\n";
      cout << "Your cuurent balance is : " << balance << endl;
   }

   void withdraw(double amount)
   {
      if (amount > balance)
      {
         cout << " Insufficient balance.\n";
         return;
      }

      balance -= amount;
      cout << " Withdrawn ₹" << amount << " successfully.\n";
      cout << "Your cuurent balance is : " << balance << endl;
   }

   void display() const
   {
      cout << "\n Account Details:\n";
      cout << "Account No: " << accountNumber << "\n";
      cout << "Name: " << holderName << "\n";
      cout << "Balance: ₹" << balance << "\n";
   }

   int getAccountNumber() const { return accountNumber; }
   double getBalance() const { return balance; }
   void addMoney(double amount) { balance += amount; }
   void deductMoney(double amount) { balance -= amount; }
};

// Bnak Class

class Bank
{
private:
   unordered_map<int, Account> accounts;

public:
   void createAccount(int accNo, const string &name)
   {
      if (accounts.find(accNo) != accounts.end())
      {
         cout << " Account number already exists.\n";
         return;
      }

      accounts[accNo] = Account(accNo, name, 0.0); // initial balance always 0
      cout << " Account created successfully!\n";
   }

   void depositToAccount(int accNo, double amount)
   {

      auto it = accounts.find(accNo);

      if (it == accounts.end())
      {
         cout << " Account not found.\n";
         return;
      }

      it->second.deposit(amount);
   }

   void withdrawFromAccount(int accNo, double amount)
   {
      auto it = accounts.find(accNo);
      if (it == accounts.end())
      {
         cout << " Account not found.\n";
         return;
      }

      it->second.withdraw(amount);
   }

   void displayAccount(int accNo) const
   {
      auto it = accounts.find(accNo);
      if (it == accounts.end())
      {
         cout << " Account not found.\n";
         return;
      }

      it->second.display();
   }

   void displayAllAccounts() const
   {
      if (accounts.empty())
      {
         cout << " No accounts to display.\n";
         return;
      }

      for (auto it = accounts.begin(); it != accounts.end(); ++it)
      {
         it->second.display();
         cout << "--------------------------\n";
      }
   }

   void transferMoney(int fromAcc, int toAcc, double amount)
   {
      if (accounts.find(fromAcc) == accounts.end() || accounts.find(toAcc) == accounts.end())
      {
         cout << " One or both accounts not found.\n";
         return;
      }

      if (accounts[fromAcc].getBalance() < amount)
      {
         cout << " Insufficient balance in sender's account.\n";
         return;
      }

      accounts[fromAcc].deductMoney(amount);
      accounts[toAcc].addMoney(amount);
      cout << "₹" << amount << " transferred successfully from " << fromAcc << " to " << toAcc << ".\n";
   }
};

// Menu

void showMenu()
{
   cout << "\n Bank Management System\n";
   cout << "1. Create Account\n";
   cout << "2. Deposit\n";
   cout << "3. Withdraw\n";
   cout << "4. Display Account\n";
   cout << "5. Display All Accounts\n";
   cout << "6. Transfer Money\n";
   cout << "7. Exit\n";
   cout << "Choose an option: ";
}

// 🔰 Main Function

const string ADMIN_PASSWORD = "1234";

int main()
{

   Bank bank;
   int choice;

   while (true)
   {
      showMenu();
      cin >> choice;

      if (choice == 7)
      {
         cout << " Exiting... Thank you!\n";
         break;
      }

      int accNo, toAcc;
      string name;
      double amount;

      switch (choice)
      {
      case 1:
         cout << "Enter Account Number & Name: ";
         cin >> accNo >> ws;
         getline(cin, name);
         bank.createAccount(accNo, name);
         break;

      case 2:
         cout << "Enter Account Number & Amount to Deposit: ";
         cin >> accNo >> amount;
         bank.depositToAccount(accNo, amount);
         break;

      case 3:
         cout << "Enter Account Number & Amount to Withdraw: ";
         cin >> accNo >> amount;
         bank.withdrawFromAccount(accNo, amount);
         break;

      case 4:
         cout << "Enter Account Number: ";
         cin >> accNo;
         bank.displayAccount(accNo);
         break;

      case 5:
      {
         string pass;
         cout << "Enter Admin Password: ";
         cin >> pass;

         if (pass != ADMIN_PASSWORD)
         {
            cout << "❌ Incorrect password. Access denied.\n";
            break;
         }

         bank.displayAllAccounts();
         break;
      }
      case 6:
         cout << "Enter Sender Acc No, Receiver Acc No & Amount: ";
         cin >> accNo >> toAcc >> amount;
         bank.transferMoney(accNo, toAcc, amount);
         break;

      default:
         cout << " Invalid option.\n";
      }
   }

   return 0;
}
