#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>
#include <vector>
#include <stdexcept>
#include <sstream>

using namespace std;

class HugeInt {
private:
    string numStr;
    string numType;

    string addStrings(const string& num1, const string& num2) const {
        string result;
        int carry = 0;
        int i = num1.length() - 1;
        int j = num2.length() - 1;

        while (i >= 0 || j >= 0 || carry > 0) {
            int digit1 = (i >= 0) ? (num1[i--] - '0') : 0;
            int digit2 = (j >= 0) ? (num2[j--] - '0') : 0;
            int sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result.push_back((sum % 10) + '0');
        }

        reverse(result.begin(), result.end());
        return result;
    }

    string multiplyStrings(const string& num1, const string& num2) const {
        int len1 = num1.size();
        int len2 = num2.size();
        vector<int> result(len1 + len2, 0);

        for (int i = len1 - 1; i >= 0; i--) {
            for (int j = len2 - 1; j >= 0; j--) {
                int product = (num1[i] - '0') * (num2[j] - '0');
                int sum = product + result[i + j + 1];
                result[i + j + 1] = sum % 10;
                result[i + j] += sum / 10;
            }
        }

        string resStr;
        for (int num : result) {
            if (!(resStr.empty() && num == 0)) {
                resStr.push_back(num + '0');
            }
        }

        return resStr.empty() ? "0" : resStr;
    }

    string hexToDecimal(const string& hex) const {
        string decimal = "0";
        for (char c : hex) {
            int digit;
            if (isdigit(c)) {
                digit = c - '0';
            } else {
                digit = toupper(c) - 'A' + 10;
            }
            decimal = multiplyStrings(decimal, "16");
            string digitStr = to_string(digit);
            decimal = addStrings(decimal, digitStr);
        }
        return decimal;
    }

    string binaryToDecimal(const string& binary) const {
        string decimal = "0";
        for (char c : binary) {
            int digit = c - '0';
            decimal = multiplyStrings(decimal, "2");
            string digitStr = to_string(digit);
            decimal = addStrings(decimal, digitStr);
        }
        return decimal;
    }

    static string decimalToHex(const string& decimal) {
        if (decimal == "0") return "0";
        string hex;
        string num = decimal;
        while (num != "0") {
            int rem = 0;
            string newNum;
            for (char c : num) {
                int digit = c - '0';
                rem = rem * 10 + digit;
                if (!newNum.empty() || rem / 16 != 0) {
                    newNum.push_back((rem / 16) + '0');
                }
                rem %= 16;
            }
            if (newNum.empty()) newNum = "0";
            if (rem < 10) {
                hex.push_back(rem + '0');
            } else {
                hex.push_back(rem - 10 + 'A');
            }
            num = newNum;
        }
        reverse(hex.begin(), hex.end());
        return hex;
    }

    static string decimalToBinary(const string& decimal) {
        if (decimal == "0") return "0";
        string binary;
        string num = decimal;
        while (num != "0") {
            int rem = 0;
            string newNum;
            for (char c : num) {
                int digit = c - '0';
                rem = rem * 10 + digit;
                if (!newNum.empty() || rem / 2 != 0) {
                    newNum.push_back((rem / 2) + '0');
                }
                rem %= 2;
            }
            if (newNum.empty()) newNum = "0";
            binary.push_back(rem + '0');
            num = newNum;
        }
        reverse(binary.begin(), binary.end());
        return binary;
    }

public:
    HugeInt() : numStr("0"), numType("Decimal") {}

    HugeInt(const string& numStr, const string& numType) : numStr(numStr), numType(numType) {
        if (numType == "Hexadecimal" || numType == "Binary") {
            transform(this->numStr.begin(), this->numStr.end(), this->numStr.begin(), ::toupper);
        }
    }

    string toDecimal() const {
        if (numType == "Decimal") {
            return numStr;
        } else if (numType == "Hexadecimal") {
            return hexToDecimal(numStr);
        } else if (numType == "Binary") {
            return binaryToDecimal(numStr);
        } else {
            throw invalid_argument("Unknown number type");
        }
    }

    static string fromDecimal(const string& decimalStr, const string& targetType) {
        if (targetType == "Decimal") {
            return decimalStr;
        } else if (targetType == "Hexadecimal") {
            return decimalToHex(decimalStr);
        } else if (targetType == "Binary") {
            return decimalToBinary(decimalStr);
        } else {
            throw invalid_argument("Unknown target type");
        }
    }

    HugeInt add(const HugeInt& other) const {
        if (numType != other.numType) {
            throw invalid_argument("Type mismatch for addition");
        }
        string decimalSelf = toDecimal();
        string decimalOther = other.toDecimal();
        string decimalSum = addStrings(decimalSelf, decimalOther);
        return HugeInt(fromDecimal(decimalSum, numType), numType);
    }

    HugeInt multiply(const HugeInt& other) const {
        if (numType != other.numType) {
            throw invalid_argument("Type mismatch for multiplication");
        }
        string decimalSelf = toDecimal();
        string decimalOther = other.toDecimal();
        string decimalProduct = multiplyStrings(decimalSelf, decimalOther);
        return HugeInt(fromDecimal(decimalProduct, numType), numType);
    }

    string getNumStr() const {
        return numStr;
    }

    string getNumType() const {
        return numType;
    }
};

void processCommand(const string& command, map<string, HugeInt>& variables) {
    istringstream iss(command);
    string token;
    vector<string> parts;
    while (iss >> token) {
        parts.push_back(token);
    }

    if (parts.empty()) {
        return;
    }

    if (parts[0] == "create") {
        string name = parts[1];
        string numType = parts[3];
        string numStr = parts[4];
        variables[name] = HugeInt(numStr, numType);
        cout << name << " as " << numType << " is " << numStr << endl;
    } else if (parts.size() >= 5 && parts[1] == "+") {
        string name1 = parts[0];
        string name2 = parts[2];
        string name3 = parts[4];
        if (variables.find(name1) == variables.end() || variables.find(name2) == variables.end()) {
            return;
        }
        try {
            HugeInt result = variables[name1].add(variables[name2]);
            variables[name3] = result;
            cout << name3 << " as " << result.getNumType() << " is " << result.getNumStr() << endl;
        } catch (const invalid_argument& e) {
            return;
        }
    } else if (parts.size() >= 5 && parts[1] == "*") {
        string name1 = parts[0];
        string name2 = parts[2];
        string name3 = parts[4];
        if (variables.find(name1) == variables.end() || variables.find(name2) == variables.end()) {
            return;
        }
        try {
            HugeInt result = variables[name1].multiply(variables[name2]);
            variables[name3] = result;
            cout << name3 << " as " << result.getNumType() << " is " << result.getNumStr() << endl;
        } catch (const invalid_argument& e) {
            return;
        }
    }
}

int main() {
    map<string, HugeInt> variables;
    string command;
    while (getline(cin, command)) {
        if (command == "end") {
            return 0;
        }
        processCommand(command, variables);
    }
    return 0;
}
