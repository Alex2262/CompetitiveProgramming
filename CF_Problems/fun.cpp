// #include <cstdio>

/*
 * Problem takeaways:
 *
 * We have to observe that we can simply loop through a and then b will be solved in O(n log n) and C by an inequality.
 *
 * Whenever we have some sort of equation like this, first think about a possible means of brute forcing it with
 * the two variables and then solving the last variable with an inequality. In this problem, it happens that we can
 * do this, and then it all works out. Don't get stuck on something that is too complex.
 */

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
const int CSES_MOD = 1'000'000'000 + 7;

void solve() {
    ll n, x;
    cin >> n >> x;

    ll ans = 0;
    for (ll i = 1; i <= x && i <= n; i++) {
        for (ll j = 1; j + i <= x && j * i <= n; j++) {
            ll c = min<ll>((n - i * j) / (i + j), x - i - j);
            if (c < 1) break;
            ans += c;
        }
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