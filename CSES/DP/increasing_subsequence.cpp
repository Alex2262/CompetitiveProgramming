// #include <cstdio>

#include <deque>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;
using ll = long long;

const ll LL_MAX = 9223372036854775807;
const int MAX = 2147483647;
const int CSES_MOD = 1'000'000'000 + 7;


void solve() {
    int n;
    cin >> n;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // The dp[i] array here represents
    // the smallest value for a sequence of length i
    // So we can loop through a[i], and update dp.
    // We binary search on elements to update, so we store the longest increasing subsequence,
    // then the last index that doesn't have an INF value is our answer.

    vector<ll> dp(n + 1, LL_MAX);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        int ind = lower_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
        if (dp[ind] == a[i]) continue;

        // cout << a[i] << " " << ind << " " << dp[ind] << " " << dp[ind + 1] << endl;
        dp[1] = min(dp[1], a[i]);
        dp[ind] = a[i];
    }

    for (int i = n; i >= 0; i--) {
        if (dp[i] != LL_MAX) {
            cout << i << endl;
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    */

}