#include <iostream>
#include <cstring>
using namespace std;

bool isValidHex(char* hex) {
    char* ptr = hex;
    while (*ptr) {
        char c = *ptr;
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))) {
            return false;
        }
        ptr++;
    }
    return true;
}

void toBinary(char* hex, char* binary) {
    int len = strlen(hex);
    char* ptr = hex;
    char* binPtr = binary;

    //  16 hex digits * 4 bits
    int totalBits = len * 4;
    int padding = 64 - totalBits;
    for (int i = 0; i < padding; i++) {
        *binPtr = '0';
        binPtr++;
    }

    while (*ptr) {
        char c = *ptr;
        int val;
        if (c >= '0' && c <= '9') val = c - '0';
        else if (c >= 'A' && c <= 'F') val = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f') val = c - 'a' + 10;

        for (int i = 3; i >= 0; i--) {
            *binPtr = ((val >> i) & 1) + '0';
            binPtr++;
        }
        ptr++;
    }
    *binPtr = '\0';
}

void my_big(char* binary) {
    char* ptr = binary;
    int len = strlen(binary);
    for (int i = 0; i < len; i += 8) {
        for (int j = 0; j < 8; j++) {
            cout << *(ptr + j);
        }
    }
    cout << endl;
}

void my_little(char* binary) {
    char* ptr = binary;
    int len = strlen(binary);
    for (int i = len - 8; i >= 0; i -= 8) {
        for (int j = 0; j < 8; j++) {
            cout << *(ptr + i + j);
        }
    }
    cout << endl;
}

int main() {
    char hex[100];
    char* ptr = hex;
    char c;
    while ((c = cin.get()) != '\n' && c != EOF) {
        *ptr = c;
        ptr++;
        if (ptr - hex >= 100) {
            break;
        }
    }
    *ptr = '\0';

    // Handle empty input
    if (strlen(hex) == 0) {
        cout << "0000000000000000000000000000000000000000000000000000000000000000" << endl;
        cout << "0000000000000000000000000000000000000000000000000000000000000000" << endl;
        cout << "0000000000000000000000000000000000000000000000000000000000000000" << endl;
        return 0;
    }

    // Check length limit
    if (strlen(hex) > 16) {
        cout << "Hexadecimal number exceeds 64-bit limit (16 hex digits)" << endl;
        return 0;
    }

    // Check for invalid digits
    if (!isValidHex(hex)) {
        cout << "Invalid hexadecimal digit" << endl;
        return 0;
    }

    char binary[65]; // 64 bits + null terminator
    toBinary(hex, binary);

    cout << binary << endl;
    my_big(binary);
    my_little(binary);

    return 0;
}
