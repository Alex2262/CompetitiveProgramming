// #include <cstdio>

#include <deque>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;
using ll = long long;

const ll LL_MAX = 9223372036854775807;
const int MAX = 2147483647;
const int CSES_MOD = 1'000'000'000 + 7;

int cycle_length(vector<vector<int>>& g, int node, int start, int k, int len) {

    if (len > k) return -k * 2;

    int ret = 0;
    for (int child : g[node]) {
        if (child == start) return 1;
        ret = cycle_length(g, child, start, k, len + 1) + 1;
    }

    return ret;
}

int dfs(vector<vector<int>>& g, vector<int>& dp, vector<bool>& visited, int node, int k) {
    // cout << "VISITING " << node << endl;

    if (dp[node] != -MAX) return dp[node];

    if (visited[node]) {
        // cout << "HOLA " << cycle_length(g, node, node, k, 0) << endl;
        return dp[node] = cycle_length(g, node, node, k, 0);
    }

    visited[node] = true;

    int ret = 0;
    for (int child : g[node]) {
        int cc = dfs(g, dp, visited, child, k);
        ret = cc == k ? cc : ret;
    }

    return dp[node] = ret;
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        b[i]--;
    }

    bool works = true;
    for (int i = 0; i < n; i++) {
        if (i == b[i] && k > 1) {
            works = false;
            break;
        }

        if (i != b[i] && k == 1) {
            works = false;
            break;
        }
    }

    if (!works) {
        cout << "NO" << endl;
        return;
    }

    vector<vector<int>> g(n);

    for (int i = 0; i < n; i++) {
        g[i].push_back(b[i]);
    }

    vector<bool> visited(n, false);
    vector<int> dp(n, -MAX);

    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;

        int len = dfs(g, dp, visited, i, k);

        // cout << i << " " << len << endl;
        if (len != k) {
            works = false;
            break;
        }
    }

    if (works) cout << "YES" << endl;
    else cout << "NO" << endl;

}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    //solve();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }



}