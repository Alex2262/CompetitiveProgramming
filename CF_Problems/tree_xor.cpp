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

using pii = pair<int, int>;
using pll = pair<ll, ll>;

const ll LL_MAX = 9223372036854775807;
const int MAX = 2147483647;
const int CSES_MOD = 1'000'000'000 + 7;

int n;

pll dfs(vector<vector<int>>& g, vector<ll>& cdp, vector<ll>& a, int parent, int node) {
    ll sum = 0, children = 1;
    for (int child : g[node]) {
        if (child == parent) continue;
        auto p = dfs(g, cdp, a, node, child);
        children += p.second;

        // cout << node << " " << child << " " << (a[node] ^ a[child]) << " " << p.second << endl;
        sum += (a[node] ^ a[child]) * p.second;
        sum += p.first;
    }

    cdp[node] = children;
    return {sum, children};
}

void root(vector<vector<int>>& g, vector<ll>& dp, vector<ll>& cdp, vector<ll>& a, int parent, int node) {
    if (parent == -1) {
        dp[node] = dfs(g, cdp, a, parent, node).first;
    } else {
        // cout << node << " " << cdp[node] << " " << cdp[parent] << endl;
        dp[node] = dp[parent];
        dp[node] -= cdp[node] * (a[parent] ^ a[node]);
        dp[node] += (cdp[parent] - cdp[node]) * (a[parent] ^ a[node]);

        cdp[node] = n;
    }

    for (int child : g[node]) {
        if (child == parent) continue;
        root(g, dp, cdp, a, node, child);
    }
}


void solve() {
    cin >> n;

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

    vector<ll> dp(n), cdp(n);

    root(g, dp, cdp, a, -1, 0);

    string s = to_string(dp[0]);
    for (int i = 1; i < n; i++) {
        s += " " + to_string(dp[i]);
    }

    cout << s << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //solve();

    // /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    // */
}