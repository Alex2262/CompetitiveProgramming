
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

ll bin_exp(ll x, ll y) {
    ll res = 1;
    x = x % MOD2;
    while (y > 0) {
        if (y & 1) res = (res * x) % MOD2;
        y = y >> 1;
        x = (x * x) % MOD2;
    }
    return res;
}

ll mod_inverse(ll n) {
    return bin_exp(n, MOD2 - 2);
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    ll sum = accumulate(a.begin(), a.end(), 0);

    vector<ll> dp(sum + 1, 0);
    dp[0] = 1;


    for (int i = 0; i < n; i++) {
        for (ll j = sum - a[i]; j >= 0; j--) {
            dp[a[i] + j] = (dp[a[i] + j] + dp[j]) % MOD2;
        }
    }


    ll ans = 0;
    for (int i = 0; i <= sum; i++) {
        ans = (ans + (((i + 1) / 2) * dp[i]) % MOD2) % MOD2;
    }

    // Fix certain values since we need to account for the dominant color
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < a[i]; j++) {
            ans = (ans + ((a[i] - (a[i] + j + 1) / 2) * dp[j]) % MOD2) % MOD2;
        }
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

