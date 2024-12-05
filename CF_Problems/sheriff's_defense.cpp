#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

// ~9 * 10 ^ 18
const ll LL_MAX = 9'223'372'036'854'775'807;

// ~2 * 10 ^ 9
const int MAX = 2'147'483'647;
const int MOD = 1'000'000'000 + 7;
// const int MOD2 = 998'244'353;

// const int N = 3e5 + 5;

/*
 *
 *
 *
 *
 *
 */


void dfs(vector<vector<int>>& g, vector<vector<ll>>& dp, vector<ll>& a, vector<bool>& rec, int node, ll c) {

    dp[node][0] = 0;
    dp[node][1] = a[node];

    for (int child : g[node]) {
        if (rec[child]) continue;

        rec[node] = true;
        dfs(g, dp, a, rec, child, c);
        rec[node] = false;

        dp[node][0] += max(dp[child][0], dp[child][1]);
        dp[node][1] += max(dp[child][0], dp[child][1] - 2 * c);
    }
}

void solve() {
    int n;
    ll c;
    cin >> n >> c;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<vector<int>> g(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<vector<ll>> dp(n, vector<ll>(2, 0));
    vector<bool> rec(n, false);

    dfs(g, dp, a, rec, 0, c);

    cout << max(dp[0][0], dp[0][1]) << endl;
}

void multi_solve() {
    int t;
    cin >> t;

    while (t--) solve();
}

int main() {

    /*
     * FAST IO
     * Remember to remove for interactive problems!!!
     * https://stackoverflow.com/questions/31162367/significance-of-ios-basesync-with-stdiofalse-cin-tienull
     */

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // solve();
    multi_solve();
}

