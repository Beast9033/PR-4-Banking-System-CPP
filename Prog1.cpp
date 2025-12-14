#include <iostream>
#include <string>

using namespace std;

class BankAccount
{
    protected:
        int accountNumber;
        string accountHolderName;
        double accountBalance;
    
    public:
        BankAccount(
            int accountNumber = 0,
            string accountHolderName = "",
            double accountBalance = 0)
        {
            this->accountNumber = accountNumber;
            this->accountHolderName = accountHolderName;
            this->accountBalance = accountBalance;
        }
    
        virtual void deposit(double depositAmount)
        {
            accountBalance += depositAmount;
            cout << "Amount Deposited Successfully!" << endl;
        }
    
        virtual void withdraw(double withdrawAmount)
        {
            if (accountBalance > withdrawAmount)
            {
                accountBalance -= withdrawAmount;
                cout << "Amount Withdraw Successfully!" << endl;
            }
            else
            {
                cout << "Amount is not sufficient for Withdrawal!" << endl;
            }
        }
    
        virtual void displayAccountInfo()
        {
            cout << "Account Number: " << accountNumber << endl;
            cout << "Account Holder Name: " << accountHolderName << endl;
            cout << "Account Balance: " << accountBalance << endl;
        }
    
        virtual double calculateInterest()
        {
            return 0;
        }
    
        double getBalance()
        {
            return accountBalance;
        }
    
        virtual ~BankAccount() {}
    };
    
    class SavingAccount : public BankAccount
    {
        double interestRate;
    
    public:
        SavingAccount(
            int accountNumber = 0,
            string accountHolderName = "",
            double accountBalance = 0,
            double interestRate = 0)
            : BankAccount(accountNumber, accountHolderName, accountBalance)
        {
            this->interestRate = interestRate;
        }
    
        double calculateInterest()
        {
            return accountBalance * interestRate / 100;
        }
    
        void displayAccountInfo()
        {
            double totalBalance = accountBalance + calculateInterest();
        
            cout << "Account Number: " << accountNumber << endl;
            cout << "Account Holder Name: " << accountHolderName << endl;
            cout << "Account Balance: " << accountBalance << endl;
            cout << "Account Total Balance (with interest): " << totalBalance << endl;
        }
    
        double getBalance()
        {
            return accountBalance + calculateInterest();
        }
    };
    
    class CheckingAccount : public BankAccount
    {
        double overdraftLimit;
    
    public:
        CheckingAccount(
            int accountNumber = 0,
            string accountHolderName = "",
            double accountBalance = 0,
            double overdraftLimit = 0)
            : BankAccount(accountNumber, accountHolderName, accountBalance)
        {
            this->overdraftLimit = overdraftLimit;
        }
    
        void withdraw(double withdrawAmount)
        {
            if (withdrawAmount <= accountBalance + overdraftLimit)
            {
                accountBalance -= withdrawAmount;
                cout << "Withdraw Successfully..." << endl;
            }
            else
            {
                cout << "Amount is more than balance. Can't withdraw..." << endl;
            }
        }
    
        double calculateInterest()
        {
            return 0;
        }
};

class FixedDepositAccount : public BankAccount
{
    int depositMonths;

public:
    FixedDepositAccount(
        int accountNumber = 0,
        string accountHolderName = "",
        double accountBalance = 0,
        int depositMonths = 0)
        : BankAccount(accountNumber, accountHolderName, accountBalance)
    {
        this->depositMonths = depositMonths;
    }

    double calculateInterest()
    {
        double interestRate = 7.5;
        return (accountBalance * interestRate * depositMonths) / (100 * 12);
    }

    void displayAccountInfo()
    {
        double totalBalance = accountBalance + calculateInterest();

        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder Name: " << accountHolderName << endl;
        cout << "Account Total Balance: " << totalBalance << endl;
    }

    double getBalance()
    {
        return accountBalance + calculateInterest();
    }

    void deposit(double depositAmount)
    {
        cout << endl << "Deposit NOT allowed in Fixed Deposit Account!" << endl;
    }

    void withdraw(double withdrawAmount)
    {
        cout << endl << "Withdrawal NOT allowed in Fixed Deposit Account!" << endl;
    }
};

int main()
{
    BankAccount *accountPointer;

    SavingAccount savingAccount;
    CheckingAccount checkingAccount;
    FixedDepositAccount fixedDepositAccount;

    int selectedAccountType;
    int selectedOperation;

    do
    {
        cout << endl << "Choose Account Type:" << endl;
        cout << "1. Saving Account" << endl;
        cout << "2. Checking Account" << endl;
        cout << "3. Fixed Deposit Account" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> selectedAccountType;

        if (selectedAccountType == 4)
        {
            cout << "Thank you for visiting..." << endl;
            break;
        }

        if (selectedAccountType > 4)
        {
            cout << "Invalid Choice!!!" << endl;
            continue;
        }

        int accountNumber;
        string accountHolderName;
        double initialBalance;

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        cout << "Enter Account Holder Name: ";
        cin >> accountHolderName;

        cout << "Enter Initial Balance: ";
        cin >> initialBalance;

        if (selectedAccountType == 1)
        {
            double interestRate;
            cout << "Enter Interest Rate: ";
            cin >> interestRate;

            savingAccount = SavingAccount(
                accountNumber,
                accountHolderName,
                initialBalance,
                interestRate);
            accountPointer = &savingAccount;
        }
        else if (selectedAccountType == 2)
        {
            double overdraftLimit;
            cout << "Enter Overdraft Limit: ";
            cin >> overdraftLimit;

            checkingAccount = CheckingAccount(
                accountNumber,
                accountHolderName,
                initialBalance,
                overdraftLimit);
            accountPointer = &checkingAccount;
        }
        else if (selectedAccountType == 3)
        {
            int depositMonths;
            cout << "Enter Fixed Deposit Months: ";
            cin >> depositMonths;

            fixedDepositAccount = FixedDepositAccount(
                accountNumber,
                accountHolderName,
                initialBalance,
                depositMonths);
            accountPointer = &fixedDepositAccount;
        }

        do
        {
            cout << endl << "Choose Account Operation:" << endl;
            cout << " 1. Deposit" << endl;
            cout << " 2. Withdraw" << endl;
            cout << " 3. Check Balance" << endl;
            cout << " 4. Calculate Interest" << endl;
            cout << " 5. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> selectedOperation;

            switch (selectedOperation)
            {
            case 1:
            {
                double depositAmount;
                cout << "Enter Deposit Amount: ";
                cin >> depositAmount;
                accountPointer->deposit(depositAmount);
                break;
            }

            case 2:
            {
                double withdrawAmount;
                cout << "Enter Withdrawal Amount: ";
                cin >> withdrawAmount;
                accountPointer->withdraw(withdrawAmount);
                break;
            }

            case 3:
                accountPointer->displayAccountInfo();
                break;

            case 4:
                cout << "Interest: "
                     << accountPointer->calculateInterest()
                     << endl;
                break;

            case 5:
                cout << "Thank you for visiting!" << endl;
                break;

            default:
                cout << "Invalid Number..." << endl;
            }

        } while (selectedOperation != 5);

    } while (true);

    return 0;
}
