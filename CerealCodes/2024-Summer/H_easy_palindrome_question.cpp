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

void dfs(vector<vector<int>>& g, vector<set<int>>& rem, set<int>& skip, int og, int node, int len) {

    if (node != og) {
        for (auto e : rem[node]) {
            rem[og].insert(e);
        }
    }

    skip.insert(node);

    for (int child : g[node]) {
        if (skip.find(child) != skip.end()) continue;
        dfs(g, rem, skip, og, child, len + 1);
    }
}


void solve() {
    ll n, m, k, q;
    cin >> n >> m >> k >> q;

    vector<int> a(n);
    vector<set<int>> rem(n);

    for (int i = 0; i < n; i++) cin >> a[i];

    bool works = true;

    for (int i = 0; i < k; i++) {
        int u, val;
        cin >> u >> val;
        u--;

        rem[u].insert(val);

        if (a[u] == val) {
            works = false;
        }
    }

    vector<vector<int>> g;
    g.reserve(n);
    for (int i = 0; i < n; i++) {
        g.emplace_back();
        g.back().reserve(n);
    }

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;

        if (l == r) continue;

        int len = (r - l + 1);

        for (int j = 0; j < len / 2; j++) {
            int left = l + j;
            int right = r - j;


            if (left >= n || left < 0 || right >= n || right < 0) {
                // cout << "FGDSKFGJDSFGSDJ" << endl;
                // return;
                continue;
            }

            if (a[left] != -1 && a[right] != -1 && a[left] != a[right]) {
                works = false;
            }

            if (a[left] != -1) a[right] = a[left];
            if (a[right] != -1) a[left] = a[right];

            g[left].push_back(right);
            g[right].push_back(left);
        }
    }

    if (!works) {
        cout << 0 << endl;
        return;
    }

    ll ans = 1;

    set<int> skip;

    for (int i = 0; i < n; i++) {
        if (a[i] != -1) continue;
        if (skip.find(i) != skip.end()) continue;

        dfs(g, rem, skip, i, i, 0);

        ll pos = m + 1 - static_cast<ll>(rem[i].size());
        pos = clamp(pos, 0LL, m + 1);

        ans = (ans * pos) % MOD;
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

    solve();
    // multi_solve();
}

