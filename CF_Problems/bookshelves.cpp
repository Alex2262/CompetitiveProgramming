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

    int max_bits = 62;

    ll ans = 0;

    for (int bit = max_bits - 1; bit >= 0; bit--) {
        // we need to figure out if there's a way to allocate all books into k bookshelves
        // such that each can have a sum >= (ans | (1 << bit)).

        ll mask = ans | (1LL << bit);

        vector<vector<bool>> dp(n + 1, vector<bool>(k + 1, false));
        dp[0][0] = true;

        // Loop through all continuous subsegments, by looping to n with i, and from i - 1 to 0 with j.
        // if we take the current elements, then we can resolve for each k shelves that
        // if shelve c works with elements before j (start of our subsegment), then if our current sum
        // can equal our mask, then this next segment is achievable.

        // i is the end of our subsegment
        for (int i = 1; i <= n; i++) {
            ll curr = 0;

            // j is the start of our subsegment
            for (int j = i - 1; j >= 0; j--) {
                curr += a[j];

                // loop through shelves
                for (int c = 0; c < k; c++) {
                    if (dp[j][c] && (curr & mask) == mask) {
                        dp[i][c + 1] = true;
                    }
                }
            }
        }

        if (dp[n][k]) {
            ans = mask;
        }

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


    solve();

    /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    */
}

