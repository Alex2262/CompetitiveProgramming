// #include <cstdio>


/*
 * Problem takeaways:
 *
 * First we must notice the fibonnacci sequence in this problem which is quite important.
 * Then, we must notice that we can represent any state using the fibonnacci sequence. Once this is realized,
 * it is simply knapsack DP with counting the number of ways.
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



ll max_fib = 25;  // something > 2 * max of x (which is 10)

ll get_bits(vector<ll>& fib, ll x) {
    int num = 0;
    for (ll i = max_fib; i >= 0; i--) {
        if (fib[i] <= x) {
            x -= fib[i];
            num++;
        }
    }

    return num;
}

void solve() {
    ll n, x, m;
    cin >> n >> x >> m;

    // It makes sense that the fibonnacci sequence appears in this problem since operations have to do with
    // two previous elements and the next element
    //
    // Each placement of pieces can be represented in a fibonacci representation (like binary, but fibonnacci).
    //
    // Know that we can transition each summed weight into the unique fibonnacci representation, which is
    // also the minimum number of chips for the same weight.

    // If the count of set bits here = m, then we know it works, since this is the minimum representation.

    vector<ll> fib(max_fib + 1, 0);
    fib[0] = 1;
    fib[1] = 1;
    for (ll i = 2; i <= max_fib; i++) fib[i] = fib[i - 1] + fib[i - 2];

    ll max_weight = fib[x - 1] * n;  // obviously this is the max weight if we put all chips at max_fib

    // count the number of ways we can achieve each weight
    // [i][j]
    // i = number of chips
    // j = weight we achieve
    vector<vector<ll>> dp(n + 1, vector<ll>(max_weight + 1, 0));

    dp[0][0] = 1;

    // This is basically knapsack DP

    // loop through possible placement
    for (ll i = 0; i < x; i++) {

        // loop through the number of coins we could use here
        for (ll j = 0; j < n; j++) {

            ll lim = j * fib[i];

            // loop through the weights we can achieve and transition
            for (ll w = 0; w <= lim; w++) {
                dp[j + 1][w + fib[i]] = (dp[j + 1][w + fib[i]] + dp[j][w]) % MOD2;
            }
        }
    }

    ll ans = 0;
    for (ll w = 0; w <= max_weight; w++) {
        if (get_bits(fib, w) == m) {
            ans = (ans + dp[n][w]) % MOD2;
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
