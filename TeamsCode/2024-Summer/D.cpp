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
    int n;
    cin >> n;

    vector<pii> inp;
    for (int i = 0; i < n; i++) {
        int t, v;
        cin >> t >> v;
        inp.emplace_back(t, v);
    }

    vector<int> dp(n, 2 * n);
    vector<int> a(n);
    vector<int> b(n);

    dp[0] = 2;
    a[0] = 1;

    int c1 = 0, c2 = 0;

    for (int i = 0; i < n; i++) {
        if (inp[i].first == 3) b[i] = inp[i].second;
        else if (inp[i].first == 2) c2++;
        else c1++;
    }



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