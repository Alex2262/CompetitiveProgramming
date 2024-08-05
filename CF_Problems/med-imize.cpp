// #include <cstdio>

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
    int n, k;
    cin >> n >> k;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    ll l = 0, r = *max_element(a.begin(), a.end());

    ll ans = 0;

    // cout << m << " " << need << endl;

    while (l <= r) {
        ll target = l + (r - l) / 2;

        vector<ll> dp(n, 0);
        vector<ll> b(n, 0);

        for (int i = 0; i < n; i++) b[i] = (a[i] >= target ? 1 : -1);

        dp[0] = b[0];

        // we have to observe that
        // index 0 of our final segment will come from index in a % k == 0
        // index 1 from index in a % k == 1
        // index 2 from index in a % k == 2
        // how do we prove this?
        // for index 0 of the final segment we know this can be achieved by making some number of segment deletions
        // of length k. All these segment deletions have to be length k, so this element must be a multiple of k
        // (including 0).
        // We can show this for all indices

        for (int i = 1; i < n; i++) {
            // We can start a new final subarray here
            if (i % k == 0) {
                dp[i] = max(dp[i - k], b[i]);
                continue;
            }

            dp[i] = dp[i - 1] + b[i];
            if (i > k) dp[i] = max(dp[i], dp[i - k]);
        }

        if (dp[n - 1] > 0) {
            ans = max(ans, target);
            l = target + 1;
        } else r = target - 1;
    }

    cout << ans << endl;
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

    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}

