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
    int n, c;
    cin >> n >> c;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> prec(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prec[i + 1] = prec[i] + (a[i] == c);
    }

    map<int, int> m;
    vector<int> dp(n + 1, 0);
    for (int i = 0; i < n; i++) {
        m[a[i]]++;
        dp[i + 1] = max(dp[i - 1], m[a[i]]);
    }


}

int main() {
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