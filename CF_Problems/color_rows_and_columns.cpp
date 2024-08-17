
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
 */

void solve() {
    ll n, k;
    cin >> n >> k;

    vector<pll> rec(n);
    for (int i = 0; i < n; i++) {
        cin >> rec[i].first >> rec[i].second;
    }

    vector<ll> dp(k + 1, LL_MAX);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        vector<ll> ndp(k + 1, LL_MAX);
        for (int j = 0; j <= k; j++) ndp[j] = min(ndp[j], dp[j]);

        ll add_ops = 0;
        ll col = rec[i - 1].first;
        ll row = rec[i - 1].second;
        ll weight = 0;

        ll max_weight = col + row;

        while (weight <= max_weight && col > 0 && row > 0) {
            if (col == 1 && row == 1) {
                col--;
                row--;
                add_ops++;
                weight = max_weight;
            } else if (col < row) {
                add_ops += col;
                row--;
                weight++;
            } else {
                add_ops += row;
                col--;
                weight++;
            }

            for (ll j = k; j >= 0; j--) {
                if (dp[j] == LL_MAX) continue;
                ll next = min(j + weight, k);
                ndp[next] = min(ndp[next], dp[j] + add_ops);
            }
        }

        dp = ndp;
    }

    if (dp[k] == LL_MAX) cout << -1 << endl;
    else cout << dp[k] << endl;
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

    // /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    // */
}

