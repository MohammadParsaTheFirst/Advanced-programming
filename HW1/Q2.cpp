#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <climits> // For INT_MAX
using namespace std;

int main() {
    vector<int> train_times;
    vector<string> train_types;
    string line;

    // Read input data
    while (true) {
        getline(cin, line);
        if (line == "end") break;
        istringstream iss(line);
        int num;
        string type;
        if (iss >> num >> type) {
            train_times.push_back(num);
            train_types.push_back(type);
        }
    }

    int K, T;
    cin >> K >> T;
    int n = train_times.size();

    // Algorithm for finding K consecutive Gold wagons with sum == T
    int sum = 0, count = 0, start = -1;

    for (int i = 0, j = 0; i < n; i++) {
        if (train_types[i] == "Gold") {
            sum += train_times[i];
            count++;
            if (count > K) {
                sum -= train_times[j];
                j++;
                count--;
            }
            if (count == K && sum == T) {
                cout << j + 1 << endl;
                return 0;
            }
        } else {
            sum = 0;
            count = 0;
            j = i + 1;
        }
    }

    // if we didnt find such order in the sequence
    int min_sum = INT_MAX, best_start = -1;
    sum = 0;
    for (int i = 0; i < K; i++) {
        sum += train_times[i];
    }
    min_sum = sum;
    best_start = 1;
    for (int i = K; i < n; i++) {
        sum += train_times[i] - train_times[i - K];
        if (sum < min_sum) {
            min_sum = sum;
            best_start = i - K + 2;
        }
    }
    cout << best_start << endl;
    return 0;
}
