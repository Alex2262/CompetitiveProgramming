// #include <cstdio>


/*
 * Problem takeaways:
 *
 * It is simple to realize that we can do some sort of bitmask DP for this problem since
 * a[i] <= 500.
 *
 * Our DP is that:
 *
 * dp[i] = the maximum value we use to achieve this value i
 *
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

    int full_mask = (1 << 10);
    vector<int> dp(full_mask, MAX);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        // dp[a[i]] = min(dp[a[i]], a[i]);
        for (int j = 0; j < full_mask; j++) {
            if (dp[j] >= a[i]) continue;
            if ((j ^ a[i]) >= full_mask) continue;

            dp[j ^ a[i]] = min(dp[j ^ a[i]], a[i]);
        }
    }

    vector<int> res;

    for (int i = 0; i < full_mask; i++) {
        if (dp[i] == MAX) continue;
        res.push_back(i);
    }

    cout << res.size() << endl;
    string s = to_string(res[0]);
    for (int i = 1; i < res.size(); i++) s += " " + to_string(res[i]);

    cout << s << endl;

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
