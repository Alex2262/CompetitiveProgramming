// #include <cstdio>

/*
 * Problem Takeaways:
 * For the most part, the observation of the cases isn't terrible.
 * We can figure out the case of 0 1 2 3 4 and 0 1 2 3 3 5 where we can skip by 2.
 *
 * The case of 0 1 2 3 3 5 3 is easily forgotten though.
 *
 * Implementation for this problem is also tricky. We need to be familiar with DP, and the idea that we always
 * multiply by 2 or add previous counts on. This is somewhat logical, but it is easy to try and do something
 * too complicated instead.
 *
 *
 *
 */
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

#define popcount    __builtin_popcount
#define popcount_ll __builtin_popcountll
#define lsb         __builtin_ctz
#define lsb_ll      __builtin_ctzll
#define msb         __builtin_clz
#define msb_ll      __builtin_clzll
#define parity      __builtin_parity

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

const ll LL_MAX = 9223372036854775807;
const int MAX = 2147483647;
// const int MOD = 1'000'000'000 + 7;
const int MOD2 = 998'244'353;


void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<ll> dp(n + 5, 0);
    vector<ll> dp2(n + 5, 0);

    ll ans = 0;

    dp[0] = 1;  // base

    const ll offset = 1;  // offset everything by 1 so we can index previously easier without more conditions
    for (int i = 0; i < n; i++) {
        ll e = a[i] + offset;

        // case 1
        dp[e] = (dp[e] * 2) % MOD2;
        dp[e] = (dp[e] + dp[e - 1]) % MOD2;

        // case 2
        dp2[e] = (dp2[e] * 2) % MOD2;
        if (a[i] > 0) dp2[e] = (dp2[e] + dp[e - 2]) % MOD2;

        // edge case of 0 1 2 3 5 3 where the 3 goes to case 2, and we add to dp2 for element 5
        dp2[e + 2] = (dp2[e + 2] * 2) % MOD2;
    }

    for (int i = 1; i <= n + offset; i++) {
        // cout << i - 1 << " " << dp[i] << " " << dp2[i] << endl;
        ans = (ans + dp[i]) % MOD2;
        ans = (ans + dp2[i]) % MOD2;
    }

    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // solve();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}
