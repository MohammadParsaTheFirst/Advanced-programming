#include <iostream>
#include <string>

using namespace std;

// Recursive function to find LCS
string LCS(string n, string m) {
    // Base case: If either string is empty, LCS is an empty string
    if (n.empty() || m.empty()) return "";

    // If the last characters match, they are part of the LCS
    if (n.back() == m.back()) {
        return LCS(n.substr(0, n.size() - 1), m.substr(0, m.size() - 1)) + n.back();
    } else {
        // Two possibilities: Remove last character from either string
        string lcs1 = LCS(n.substr(0, n.size() - 1), m);
        string lcs2 = LCS(n, m.substr(0, m.size() - 1));

        // Return the longer sequence
        return (lcs1.size() > lcs2.size()) ? lcs1 : lcs2;
    }
}

int main() {
    string n, m;

    cin >> n >> m;

    cout << LCS(n, m) << endl;

    return 0;
}
