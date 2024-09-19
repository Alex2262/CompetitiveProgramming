#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <deque>
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <functional>

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


void dfs(vector<vector<int>>& g, vector<int>& c, vector<ll>& dp, int node, int parent, ll& ans) {

    dp[c[node]]++;
    ll start = dp[c[node]];

    for (int child : g[node]) {
        if (child == parent) continue;
        ll start2 = dp[c[node]];
        dfs(g, c, dp, child, node, ans);
        ll amt2 = dp[c[node]] - start2;
        ans += amt2 * (amt2 - 1) / 2;
    }

    ll amt = dp[c[node]] - start;
    ans += amt;
    dp[c[node]] = start;
}

void solve() {
    int n;
    cin >> n;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        c[i]--;
    }

    vector<vector<int>> g(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    ll ans = 0;
    vector<ll> dp(n, 0);

    dfs(g, c, dp, 0, -1, ans);

    for (int i = 0; i < n; i++) {
        ans += dp[i] * (dp[i] - 1) / 2;
    }

    cout << ans << endl;
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

