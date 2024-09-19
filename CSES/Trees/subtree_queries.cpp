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



const int N = 2e5 + 5;
ll tree[N * 2];
int n;

void build() {
    for (int i = n - 1; i > 0; i--) tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void modify_point(int p, ll value) {
    p += n;
    tree[p] = value;
    for (; p > 1; p >>= 1) tree[p >> 1] = tree[p] + tree[p ^ 1];
}

ll query_range(int l, int r) {
    l += n, r += n;
    ll res = 0;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res += tree[l++];
        if (r & 1) res += tree[--r]; // Remember that r is the excluded bound
    }

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
    int q;
    cin >> n >> q;

    vector<vector<int>> g(n);

    vector<ll> a(n, 0);

    for (int i = 0; i < n; i++) cin >> a[i];

    build();

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<bool> vis(n, false);
    vector<int> start(n, 0);
    vector<int> end(n, 0);

    int timer = 0;
    dfs(g, vis, start, end, 0, timer);

    for (int i = 0; i < n; i++) {
        modify_point(start[i], a[i]);
    }

    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;

        int v;
        cin >> v;
        v--;

        if (t == 1) {
            ll x;
            cin >> x;

            modify_point(start[v], x);
        } else {
            ll res = query_range(start[v], end[v]);
            cout << res << endl;
        }
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




