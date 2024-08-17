
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
// const int MOD = 1'000'000'000 + 7;
const int MOD2 = 998'244'353;

// const int N = 3e5 + 5;

/*
 *
 *
 *
 *
 *
 */


ll dfs(vector<vector<int>>& g, vector<ll>& a, vector<ll>& dp, vector<bool>& rec, int node, ll lim) {
    // cout << node << " " << lim << endl;

    if (rec[node]) return 1e18 + 5;
    if (dp[node] != -1) return dp[node];

    ll best = 0;
    for (int child : g[node]) {
        if (a[child] > lim) continue;

        rec[node] = true;
        best = max(best, dfs(g, a, dp, rec, child, lim) + 1);
        rec[node] = false;
    }

    return dp[node] = best;
}

void solve() {
    int n, m;
    cin >> n >> m;
    ll k;
    cin >> k;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<vector<int>> g(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        g[u].push_back(v);
    }

    ll mx = *max_element(a.begin(), a.end());

    ll l = 0, r = mx;
    ll ans = 0;

    bool found = false;

    while (l <= r) {
        ll mid = l + (r - l) / 2;

        vector<ll> dp(n, -1);
        vector<bool> rec(n, false);

        ll best = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] > mid) continue;
            best = max(best, dfs(g, a, dp, rec, i, mid) + 1);
        }

        if (best >= k) {
            found = true;
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }

    if (!found) cout << -1 << endl;
    else cout << ans << endl;

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

    /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    */
}

