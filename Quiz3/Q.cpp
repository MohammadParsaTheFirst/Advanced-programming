#include <iostream>
#include <string>

#include <vector>
#include <algorithm>
#include <limits>
#include <unordered_map>

using namespace std;

class Admin {
private:
    unordered_map<string, string> users;
    vector<string> signupOrder;

public:// doesnt work for multiple sign ups? --------------------------------------
    void signUp(const string& username, const string& password) {
        if (users.find(username) != users.end()) {
            cout << "This username is already taken" << endl;
            return;
        }
        if (password.length() < 6) {
            cout << "Password must be at least 6 characters long" << endl;
            return;
        }
        users[username] = password;
        signupOrder.push_back(username);
        cout << "Account created successfully!" << endl;
    }

    void logIn(const string& username, const string& password) {
        if (users.find(username) == users.end()) {
            cout << "The username is not registered" << endl;
            return;
        }
        if (users[username] != password) {
            cout << "Password is incorrect" << endl;
            return;
        }
        cout << "Logged in successfully!" << endl;
    }

    void changePassword(const string& username, const string& password, const string& newPassword) {
        if (users.find(username) == users.end() || users[username] != password) {
            cout << "Invalid username or password" << endl;
            return;
        }
        if (newPassword.length() < 6) {
            cout << "New password must be at least 6 characters long" << endl;
            return;
        }
        users[username] = newPassword;
        cout << "Password changed successfully!" << endl;
    }

    void showUsers() {
        for (const string& username : signupOrder) {
            cout << username << endl;
        }
    }
};

// Helper function to trim whitespace from both ends of a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

int main() {
    Admin system;
    string command;

    while (true) {
        getline(cin, command);
        command = trim(command);

        if (command.empty()) continue;
        //
        if (command == "exit") {
            // break;
            return 0;
        }
        // Sign up <uname> <pass>
        else if (command == "Sign up") {
            string username, password;
            getline(cin, username);
            getline(cin, password);
            system.signUp(trim(username), trim(password));
        }
        // Log in <Uname> <pass>
        else if (command == "Log in") {
            string username, password;
            getline(cin, username);
            getline(cin, password);
            system.logIn(trim(username), trim(password));
        }
        // Change Password <uname> <pass1> <pass2>
        else if (command == "Change password") {
            string username, currentPassword, newPassword;
            getline(cin, username);
            getline(cin, currentPassword);
            getline(cin, newPassword);
            system.changePassword(trim(username), trim(currentPassword), trim(newPassword));
        }
        else if (command == "Show users") {
            system.showUsers();
        }
        else {
            cout << "Invalid command" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return 0;
}
