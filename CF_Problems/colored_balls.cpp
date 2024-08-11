
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


void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    ll mx = *max_element(a.begin(), a.end());
    vector<vector<pll>> dp(n + 1, vector<pll>(mx + 1, {0, 0}));

    dp[0][0] = {1, 0};
    for (int i = 1; i <= n; i++) {
        ll x = a[i - 1];
        for (ll j = 0; j <= mx; j++) dp[i][j] = dp[i - 1][j];

        for (ll j = mx; j >= 0; j--) {
            if (dp[i - 1][j].first) {
                ll rem = x > j ? x - j : j - x;
                if (rem > mx) continue;
                cout << "FOUND " << j << " " << rem << endl;
                dp[i][rem].first = (dp[i][rem].first + dp[i - 1][j].first) % MOD2;
                dp[i][rem].second = (dp[i][rem].second + ((dp[i - 1][j].first * x) % MOD2) % MOD2) % MOD2;
                cout << "DP j " << dp[i - 1][j].first << " " << dp[i - 1][j].second << endl;
                cout << "DP " << dp[i][rem].first << " " << dp[i][rem].second << endl;
            }
        }

        for (ll j = 0; j <= mx; j++) {
            cout << i << " " << j << " " << dp[i][j].first << " " << dp[i][j].second << endl;
        }
    }

    ll ans = 0;
    for (int i = 0; i <= mx; i++) {
        ans = (ans + dp[n][i].second) % MOD2;
    }

    cout << ans << endl;

    /*
     *  4
     *  1 3 3 7
     *
     *  0. {} = 0           | 0
     *  1. {1} = 1          | 1
     *  2. {3} = 3          | 3
     *  3. {3} = 3          | 3
     *  4. {7} = 7          | 7
     *  5. {1 3} = 3        | 2
     *  6. {1 3} = 3        | 2
     *  7. {1 7} = 7        | 6
     *  8. {3 3} = 3        | 0
     *  9. {3 7} = 7        | 4
     *  10. {3 7} = 7       | 4
     *  11. {1 3 3} = 4     | 1
     *  12. {1 3 7} = 7     | 3
     *  13. {1 3 7} = 7     | 3
     *  14. {3 3 7} = 7     | 1
     *  15. {1 3 3 7} = 7   | 0
     *
     *  0: 10
     *  1: 12
     *  2: 6
     *  3: 20
     *  4: 14
     *  5: 0
     *  6: 7
     *  7: 7
     *
     *  == 76
     *
     */

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

