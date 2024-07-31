// #include <cstdio>

/*
 * Problem takeaways:
 *
 * We should always write out the equations we can see.
 * But first, we must make the observation for this problem that we can solve for [x, y] and see
 * what larger subsets they apply to. Obviously, it will apply to (x + 1) * (n - y) since there are x + 1 elements
 * to the left, and n - y elements to the right inclusive.
 *
 * We must then notice that all [x, y] work if: prefix_sum[j] - prefix_sum[i] = 0
 * so prefix_sum[j] = prefix_sum[i]
 *
 * Then, we need to take care of all places where prefix_sum is equal, because then these can form a valid [x, y].
 * With setting up equations, we can optimize certain sums in linear time.
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
    string s;
    cin >> s;

    ll n = s.size();

    vector<ll> pre(n * 2 + 1, 0);

    ll curr = n;
    ll ans  = 0;

    pre[curr] += 1;

    for (int i = 0; i < n; i++) {
        if (s[i] == '1') curr++;
        else curr--;

        // cout << n + curr << " " << pre[n + curr] << endl;
        ans = (ans + ((pre[curr] * (n - i)) % MOD)) % MOD;
        pre[curr] = (pre[curr] + (i + 2)) % MOD; // represents the next index (i + 1) and then + 1 because we include it
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