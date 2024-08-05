// #include <cstdio>

/*
 * Problem takeaways:
 *
 * We were able to come up with the binary search approach to find the maximum for this problem,
 *
 * however, we need to think how we could use DP to check solution.
 *
 * We can first come up with a DP approach in n^2 that is just by observing each segment can be <= target, so
 * we DP on the elements we want to block. Then, we can optimize this to O(n log n).
 *
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

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<ll> pre(n + 1, 0);
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + a[i];

    /*
    vector<ll> dp(n + 2, LL_MAX);

    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        dp[i] = max(a[i -  1], pre[i - 1]);


    }
     */

    ll l = 0, r = pre[n];
    while (l < r) {
        ll mid = l + (r - l) / 2;

        /*
         * Our DP is that we want to choose the minimum number of elements to block such that
         * each segment in between the elements we pick is <= mid (this is the value we try to prove works).
         *
         * This DP can be done in O(n^2), by looping through i (each element we try to block), then looping through
         * j such that j < i.
         *
         * We optimize this to O(n log n) with multiset and sliding window by keeping track of the last few DP
         * elements in our window (this window can only have curr <= mid).
         *
         *
         */
        vector<ll> dp(n + 1, LL_MAX);

        dp[0] = 0;

        multiset<ll> ms;
        ms.insert(0);

        ll curr = 0;
        int left = 0;

        // cout << "TARGET " << mid << endl;

        for (int i = 0; i < n; i++) {
            while (curr > mid) {
                curr -= a[left];
                if (ms.find(dp[left]) != ms.end()) ms.erase(ms.find(dp[left]));
                left++;
            }

            dp[i + 1] = min(dp[i + 1], *ms.begin() + a[i]);
            ms.insert(dp[i + 1]);

            // cout << i << " " << dp[i + 1] << " " << curr << " " << left << endl;

            curr += a[i];
        }

        ll score = LL_MAX;
        for (int j = n - 1; j >= 0; j--) {
            // ensure the segment between index n and j is <= mid
            if (pre[n] - pre[j + 1] > mid) {
                break;
            }

            score = min(score, dp[j + 1]);
        }

        if (score > mid) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    cout << l << endl;

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

