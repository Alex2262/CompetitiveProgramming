// #include <cstdio>

/*
 * Problem takeaways:
 *
 * It's important to realize that this doesn't have anything to do with prime factorization.
 * That was my initial thought, but then you can realize it's DP.
 *
 * You realize this because the answer is just n - the longest increasing subsequence that divides each other
 * successfully.
 *
 * we have dp[i] = length of subsequence, where i = number.
 *
 * so for each a[i], we just find the factors of it, do dp[a[i]] = max(dp[a[i]], dp[factors] + 1)
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
// const int MOD2 = 998'244'353;



void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    int mx = a[n - 1];

    vector<int> dp(mx + 1, 0);
    // dp[1] = 1;

    for (int i = 0; i < n; i++) {
        dp[a[i]] += 1;
        for (int j = 1; j <= sqrt(a[i]); j++) {
            if (a[i] % j == 0) {
                if (a[i] / j == j) {
                    if (j != a[i]) dp[a[i]] = max(dp[a[i]], dp[j] + 1);
                }
                else {
                    // cout << a[i] / j << " " << j << " " << dp[j] << " " << dp[a[i] / j] << endl;
                    if (j != a[i]) dp[a[i]] = max(dp[a[i]], dp[j] + 1);
                    if (a[i] / j != a[i]) dp[a[i]] = max(dp[a[i]], dp[a[i] / j] + 1);
                }
            }
        }

        // cout << i << " " << a[i] << " " << dp[a[i]] << endl;
    }

    int ans = 0;
    for (int i = 0; i <= mx; i++) {
        ans = max(ans, dp[i]);
    }

    cout << max(n - ans, 0) << endl;
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
