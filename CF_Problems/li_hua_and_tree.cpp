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

struct custom {
    bool operator()(const pll& a, const pll& b) const {
        return a.first > b.first || (a.first == b.first && a.second < b.second);
    }
};

vector<int> parents;
vector<ll> pre;
vector<ll> presz;

pll dfs(vector<vector<int>>& g, vector<set<pll, custom>>& s, vector<ll>& a, int node, int parent) {

    parents[node] = parent;

    ll sum = a[node];
    ll sz = 1;

    for (int child : g[node]) {
        if (child == parent) continue;

        auto p = dfs(g, s, a, child, node);
        sum += p.first;
        sz += p.second;

        s[node].insert({p.second, child});
    }

    pre[node] = sum;
    presz[node] = sz;

    return {sum, sz};
}

void solve() {
    int n, m;
    cin >> n >> m;

    parents.reserve(n);
    parents.resize(n);

    pre.reserve(n);
    pre.resize(n);

    presz.reserve(n);
    presz.resize(n);

    vector<ll> a(n);

    for (int i = 0; i < n; i++) cin >> a[i];

    vector<vector<int>> g(n);

    vector<set<pll, custom>> s(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(g, s, a, 0, -1);

    for (int q = 0; q < m; q++) {
        int t, x;
        cin >> t >> x;

        x--;

        if (t == 1) {
            cout << pre[x] << endl;
            continue;
        }

        if (s[x].empty()) continue;

        // cout << "WHAT " << t << " " << x + 1 << endl;

        auto it = s[x].begin();
        auto p = *it;
        int y = p.second;

        int z = parents[x];

        s[z].erase(s[z].find({presz[x], x}));

        presz[x] -= presz[y];
        pre[x] -= pre[y];

        s[x].erase(it);

        pre[y] += pre[x];
        presz[y] += presz[x];

        s[z].insert({presz[y], y});
        s[y].insert({presz[x], x});

        parents[x] = y;
        parents[y] = z;
    }
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

    // ios_base::sync_with_stdio(false);
    // cin.tie(nullptr);

    solve();
    // multi_solve();
}

