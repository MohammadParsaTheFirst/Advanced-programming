#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

std::vector<std::string> tokenize(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

class Customer {
private:
    float balance;
    string name;
    string accountNumber;
    string nationalID;
public:
    static vector<Customer> customerList;

    static void addCustomerToList(const Customer& customer) {
        customerList.push_back(customer);
    }

    void deposit(float amount) {///////////////////////////////////////////
        float x = balance;
        this->setBalance(x + amount);
    }

    bool withdraw(float amount) {///////////////////////////////////////////
        if (amount > balance) {
            return false;
        }
        float x = balance;
        setBalance(x - amount);
        return true;
    }

    void setBalance(float newBalance) {
        balance = newBalance;
    }
    string getName() const {
        return name;
    }
    string getAccountNumber() const {
        return accountNumber;
    }
    string getNationalID() const {
        return nationalID;
    }
    float getBalance() const {
        return balance;
    }

    Customer(float balance, string name, string accountNumber, string nationalID) {
        this->balance = balance;
        this->name = name;
        this->accountNumber = accountNumber;
        this->nationalID = nationalID;
        Customer::addCustomerToList(*this);// jaleb
    }


};

class BankAccount {
public:
    static double annualInterestRate;
    static double taxRate;
    static bool interestRateSet;
    static bool taxRateSet;

    static void setInterestRate(double rate) {
        annualInterestRate = rate;
        interestRateSet = true;
    }

    static void setTaxRate(double rate) {
        taxRate = rate;
        taxRateSet = true;
    }

    static void applyInterestToAll() {
        if (!interestRateSet) return;

        cout << "Interest applied." << endl;
        for (auto& customer : Customer::customerList) {
            float oldBalance = customer.getBalance();
            float interest = oldBalance * (annualInterestRate / 100);
            float newBalance = oldBalance + interest;
            customer.setBalance(newBalance);
            cout << customer.getName() << ": " << fixed << setprecision(2)
                 << oldBalance << " => " << newBalance << endl;
        }
    }

    static void applyTaxToAll() {
        if (!taxRateSet) {
            cout << "Error! Tax rate not set." << endl;
            return;
        }

        cout << "Tax applied." << endl;
        for (auto& customer : Customer::customerList) {
            float oldBalance = customer.getBalance();
            float tax = oldBalance * (taxRate / 100);
            float newBalance = oldBalance - tax;
            customer.setBalance(newBalance);
            cout << customer.getName() << ": " << fixed << setprecision(2)
                 << oldBalance << " => " << newBalance << endl;
        }
    }
};

vector<Customer> Customer::customerList;
double BankAccount::annualInterestRate = 0.0;
double BankAccount::taxRate = 0.0;
bool BankAccount::interestRateSet = false;
bool BankAccount::taxRateSet = false;

Customer* findCustomerByAccountNumber(const string& accountNumber) {
    for (auto& customer : Customer::customerList) {
        if (customer.getAccountNumber() == accountNumber) {
            return &customer;
        }
    }
    return nullptr;
}

void handleCommand(vector<string> args) {
    if (args.empty())
        return;
    //add_customer <name> <national_ID> <accountNumber> <initialBalance>
    if (args[0]=="add_customer") {
        if (args.size() < 5) {
            cout << "invalid command!" << endl;
            return;
        }
        string name = args[1];
        string nationalID = args[2];
        string accountNumber = args[3];
        float balance = stof(args[4]);
        bool nameExists = false, idExists= false, accountExists =false;

        for (const auto& customer : Customer::customerList) {
            if (customer.getName() == name)
                nameExists = true;
            if (customer.getNationalID() == nationalID)
                idExists = true;
            if (customer.getAccountNumber() == accountNumber)
                accountExists = true;
        }

        // If any are found, notify the user and don't create a new Customer
        if (nameExists || idExists || accountExists) {
            if (nameExists)
                cout << "Error! this name is already registered." << endl;
            else if (idExists)
                cout << "Error! this national_ID is already registered." << endl;
            else if (accountExists)
                cout << "Error! this accountNumber is already registered." << endl;
            return;
        }
        Customer newCustomer(balance, name, accountNumber, nationalID);
        cout << "Customer "+name +" added. Account: " + accountNumber << endl;
    }
    //deposit <accountNumber> <amount>
    else if (args[0] == "deposit") {
        if (args.size() < 3) {
            cout << "invalid command!" << endl;
            return;
        }
        string accountNumber = args[1];
        float amount = stof(args[2]);
        if (amount<0) {
            cout << "invalid command!" << endl;
            return;
        }
        Customer* customer = findCustomerByAccountNumber(accountNumber);
        ////////////////////////////////////////////////////////////////////////////
        if (customer!= nullptr) {
            customer->deposit(amount);
            cout << "Deposit successful. New balance: " << fixed << setprecision(2) <<customer->getBalance() << endl;
        }
    }
    //withdraw <accountNumber> <amount>
    else if (args[0] == "withdraw") {
        if (args.size() < 3) {
            cout << "invalid command!" << endl;
            return;
        }
        string accountNumber = args[1];
        float amount = stof(args[2]);
        Customer* customer = findCustomerByAccountNumber(accountNumber);
        if (customer!= nullptr) {
            if (customer->withdraw(amount)) {
                //customer->setBalance()
                cout << "Withdrawal successful. New balance: " << fixed << setprecision(2) << customer->getBalance() << endl;
            } else {
                cout << "Error! Insufficient funds" << endl;
            }
        }
    }
    //balance <accountNumber>
    else if (args[0] == "balance") {
        if (args.size() < 2) {
            cout << "invalid command!" << endl;
            return;
        }
        string accountNumber = args[1];
        Customer* customer = findCustomerByAccountNumber(accountNumber);
        if (customer) {
            cout << "Account " << accountNumber << " balance: "
                 << fixed << setprecision(2) << customer->getBalance() << endl;
        }
    }
    //show_all
    else if (args[0] == "show_all") {
        for (const auto& customer : Customer::customerList) {
            cout << customer.getName() << " "
                 << customer.getNationalID() << " "
                 << customer.getAccountNumber() << " "
                 << fixed << setprecision(2) << customer.getBalance() << endl;
        }
    }
    //set_interest <rate>
    else if (args[0] == "set_interest") {
        if (args.size() < 2) {
            cout << "invalid command!" << endl;
            return;
        }
        double rate = stod(args[1]);
        BankAccount::setInterestRate(rate);
        cout << "Interest rate set to " << fixed << setprecision(2) << rate << "%" << endl;
    }
    //set_tax <rate>
    else if (args[0] == "set_tax") {
        if (args.size() < 2) {
            cout << "invalid command!" << endl;
            return;
        }
        double rate = stod(args[1]);
        BankAccount::setTaxRate(rate);
        cout << "Tax rate set to " << fixed << setprecision(2) << rate << "%" << endl;
    }
    //apply_interest
    else if (args[0] == "apply_interest") {
        if (!BankAccount::interestRateSet) {
            cout << "invalid command!" << endl;
            return;
        }
        BankAccount::applyInterestToAll();
    }
    //apply_tax
    else if (args[0] == "apply_tax") {
        if (!BankAccount::taxRateSet) {
            cout << "invalid command!" << endl;
            return;
        }
        BankAccount::applyTaxToAll();
    }
    //invalid command!
    else {
        cout<< "invalid command!"<< endl;
    }
}

int main() {

    // string input;
    // cin >> input;
    // while (input != "exit") {
    //     vector<string> tokens = tokenize(input, ' ');
    //     handleCommand(tokens);
    //     cin >> input;
    // }
    string input;
    while (true) {
        getline(cin, input);
        if (input == "exit") {
            break;
        }
        vector<string> tokens = tokenize(input, ' ');
        handleCommand(tokens);
    }
    cout << "Goodbye!" << endl;
    return 0;
}




