#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> strings(n);
    for (int i = 0; i < n; ++i) {
        cin >> strings[i];
    }

    unordered_map<string, vector<string>> groups;
    vector<string> keys;

    for (const string& s : strings) {
        string sorted = s;
        sort(sorted.begin(), sorted.end());
        if (groups.find(sorted) == groups.end()) {
            keys.push_back(sorted);
        }
        groups[sorted].push_back(s);
    }

    for (const string& key : keys) {
        cout << "[";
        for (size_t i = 0; i < groups[key].size(); ++i) {
            if (i != 0) {
                cout << ", ";
            }
            cout << groups[key][i];
        }
        cout << "]" << endl;
    }

    return 0;
}
