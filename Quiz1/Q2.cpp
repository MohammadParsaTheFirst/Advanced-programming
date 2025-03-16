#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int max_experience(int n, int k, vector<int>& a, vector<int>& b) {
    int max_exp = 0;
    int current_exp = 0;
    int max_b = 0;

    for (int t = 0; t < min(n, k); ++t) {
        current_exp += a[t];
        max_b = max(max_b, b[t]);
        int remaining = k - (t + 1);
        max_exp = max(max_exp, current_exp + remaining * max_b);
    }

    return max_exp;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    cout << max_experience(n, k, a, b) << endl;
    return 0;
}
