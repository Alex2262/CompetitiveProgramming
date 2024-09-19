// #pragma GCC optimize("O3,unroll-loops")
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


#define popcount    __builtin_popcount



const int N = 5e5 + 5;
ll tree[N * 2] {};
int n;

void modify_range(int l, int r, ll value) {
    l += n, r += n;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) tree[l++] += value;
        if (r & 1) tree[--r] += value;
    }
}

// QUERY POINT
// O(log(n))
// If we ever use this we cannot build the tree!!!!!
// We only store the updates in the segtree.
ll query_point(int p) {
    p += n;
    ll res = 0;
    for (; p > 0; p >>= 1) res += tree[p];
    return res;
}


void dfs(vector<vector<int>>& g, vector<bool>& vis, vector<int>& start, vector<int>& end, int node, int& timer) {
    start[node] = timer;
    timer++;

    vis[node] = true;

    for (int child : g[node]) {
        if (vis[child]) continue;
        dfs(g, vis, start, end, child, timer);
    }

    end[node] = timer;
}

void solve() {

    n = 1;

    int q;
    cin >> q;

    vector<vector<int>> g;
    g.emplace_back();

    vector<pll> qs;

    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;

        if (t == 1) {
            int v;
            cin >> v;
            v--;

            int node = g.size();
            g.emplace_back();
            g[v].push_back(node);

            qs.emplace_back(node, LL_MAX);

            continue;
        }

        int v;
        ll amt;
        cin >> v >> amt;
        v--;

        qs.emplace_back(v, amt);
    }

    n = g.size();
    // cout << "N " << n << endl;

    vector<bool> vis(n, false);
    vector<int> start(n, 0);
    vector<int> end(n, 0);

    int timer = 0;
    dfs(g, vis, start, end, 0, timer);

    for (int i = 0; i < 2 * n; i++) tree[i] = 0;

    for (int i = 0; i < q; i++) {
        ll v = qs[i].first;

        if (qs[i].second == LL_MAX) {
            ll curr = query_point(start[v]);
            modify_range(start[v], end[v], -curr);

            // cout << "REMOVE " << v << " " << curr << endl;
            continue;
        }

        // cout << "ADD " << v << " " << qs[i].second << endl;
        modify_range(start[v], end[v], qs[i].second);
    }

    string s;
    for (int i = 0; i < n; i++) {
        s += to_string(query_point(start[i]));
        if (i != n - 1) s += " ";
    }

    cout << s << endl;
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

    // solve();
    multi_solve();
}




