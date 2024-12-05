#pragma GCC optimize("O2,unroll-loops")
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
const ll MOD = 1'000'000'000 + 7;
// const ll MOD = 998'244'353;


/*
 *
 *
 *
 */



pii dfs(vector<vector<int>>& g, int node, int parent, int len) {

    if (g[node].size() == 1) {
        return {1, 1};
    }

    int mn = MAX;
    int tot = 0;
    for (int child : g[node]) {
        if (child == parent) continue;
        pii res = dfs(g, child, node, len + 1);
        mn = min(mn, res.first);
        tot += res.second;
    }


    if (mn <= len) {
        tot = 1;
    }

    return {mn + 1, tot};
}


void solve() {
    int n, k;
    cin >> n >> k;

    k--;

    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        u--, v--;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    pii ans = dfs(g, k, k, 0);

    cout << ans.second << endl;
}

void multi_solve() {
    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        solve();
    }
}

int main() {

    /*
     * FAST IO
     * Remember to remove for interactive problems!!!
     * https://stackoverflow.com/questions/31162367/significance-of-ios-basesync-with-stdiofalse-cin-tienull
     */

    freopen("atlarge.in", "r", stdin);
    freopen("atlarge.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}


