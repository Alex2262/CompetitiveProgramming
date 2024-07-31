// #include <cstdio>

/*
 * Problem takeaways:
 *
 * We can first guess that this is likely a bitmasking problem due to the nature of c <= 18.
 * Then, we think about transitions.
 *
 * If we have a good subset, we cannot say that all subsets smaller than this are good.
 * however, if we have a bad subset, we can say that all subsets smaller than this are bad, so
 * we aim to determine bad subsets.
 *
 * First, we must observe that all subsets without the last element of the string are bad.
 * Next, we must observe that if we have a set of elements, and there is every a length of k where none
 * of our elements are in this length of k, then this set is bad.
 *
 * So, we use sliding window through all windows of length k, and for each element not in this window of length k
 * we union them to form a large bad set of elements. Then, it is easy to determine any smaller bad subsets
 * using bitmask DP.
 *
 *
 * How would we solve this during a contest? First we must think about how bitmasking DP would work.
 * We need to recognize that we have to be able to determine bad subsets. Once we determine this, the
 * rest of the problem is not too hard.
 *
 *
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
const int MOD = 1'000'000'000 + 7;

void solve() {
    ll n, c, k;
    cin >> n >> c >> k;

    string s;
    cin >> s;

    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = s[i] - 'A';

    ll max_bits = (1 << c);
    vector<bool> bad(max_bits, false);

    // All good subsets must contain the last letter, so if it doesn't it's bad.
    bad[(max_bits - 1) ^ (1 << a[n - 1])] = true;
    bad[0] = true;

    vector<vector<int>> counts(c, vector<int>(n + 1, 0));

    for (int i = 0; i < c; i++) {
        for (int j = 0; j < n; j++) {
            counts[i][j + 1] = counts[i][j] + (a[j] == i);
        }
    }

    // Sliding window of length K
    for (int i = 0; i <= n - k; i++) {
        ll bad_mask = 0;

        // If any letters do not appear in this window of length K, they all must be bad, so we can form
        // a large subset containing all of these letters.
        for (int j = 0; j < c; j++) {
            if (counts[j][i + k] - counts[j][i] == 0) {
                bad_mask |= 1 << j;
            }
        }

        bad[bad_mask] = true;
    }

    ll best = LL_MAX;

    for (ll i = c; i >= 1; i--) {
        for (int j = 0; j < max_bits; j++) {
            if (popcount(j) != i) continue;

            if (!bad[j]) {
                // cout << j << " " << i << endl;
                best = min(best, i);
                continue;
            }

            for (int t = 0; t < c; t++) {
                if (!(j & (1 << t))) continue;
                bad[j ^ (1 << t)] = true;
            }
        }
    }

    cout << best << endl;
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