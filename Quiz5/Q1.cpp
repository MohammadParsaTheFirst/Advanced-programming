#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N, K, S, T;
vector<vector<int>> adj;
int dp[16][1 << 16]; // dp[current_vertex][mask]

int dfs(int u, int mask, int count) {
    if (count == K) {
        return (u == T) ? 1 : 0;
    }
    if (dp[u][mask] != -1) {
        return dp[u][mask];
    }
    int res = 0;
    for (int v = 0; v < N; ++v) {
        if (adj[u][v] && !(mask & (1 << v))) {
            res += dfs(v, mask | (1 << v), count + 1);
        }
    }
    return dp[u][mask] = res;
}

int main() {
    cin >> N >> K;
    adj.resize(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> adj[i][j];
        }
    }
    cin >> S >> T;
    memset(dp, -1, sizeof(dp));
    int initial_mask = 1 << S;
    int ans = dfs(S, initial_mask, 1);
    cout << ans << endl;
    return 0;
}
