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
 * notes:
 *
 * for odd n, we should notice the answer is always 1.
 *
 * for even:
 * there need to be k / 2 nodes in one subtree and k / 2 above it for it to be good.
 *
 *
 *
 *
 *
 *
 */


ll bin_exp(ll x, ll y) {
    ll res = 1LL;
    while (y > 0) {
        if (y & 1LL) res = (res * x) % MOD;
        x = (x * x) % MOD;
        y = y >> 1LL;
    }

    return res;
}

ll mod_inverse(ll n) {
    return bin_exp(n, MOD - 2LL);
}

ll binomial(vector<ll>& fac, vector<ll>& inv, ll n, ll r) {
    if (r == 0 || r > n) return 0LL;
    return (((fac[n] * inv[r]) % MOD) * inv[n - r]) % MOD;
}


ll dfs(vector<vector<int>>& g, vector<ll>& fac, vector<ll>& inv, int node, int parent, ll n, ll k, ll& ans) {

    ll sz = 1LL;
    for (int child : g[node]) {
        if (child == parent) continue;

        ll csz = dfs(g, fac, inv, child, node, n, k, ans);
        sz += csz;

        ans = (ans + (binomial(fac, inv, csz, k / 2LL) * binomial(fac, inv, n - csz, k / 2LL)) % MOD) % MOD;
    }

    return sz;
}

void solve() {
    ll n, k;
    cin >> n >> k;

    vector<vector<int>> g(n);

    if (k & 1) {
        cout << 1 << endl;
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    ll ans = 0LL;

    vector<ll> fac(n + 1, 1LL);
    vector<ll> inv(n + 1, 1LL);

    for (ll i = 2LL; i <= n; i++) fac[i] = (fac[i - 1] * i) % MOD;
    for (ll i = 1LL; i <= n; i++) inv[i] = mod_inverse(fac[i]) % MOD;

    dfs(g, fac, inv, 0, -1, n, k, ans);

    ans = (ans * mod_inverse(binomial(fac, inv, n, k))) % MOD;
    ans = (ans + 1LL) % MOD;

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

    // ios_base::sync_with_stdio(false);
    // cin.tie(nullptr);

    solve();
    // multi_solve();
}

