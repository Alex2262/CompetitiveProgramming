#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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
#include <numeric>
#include <functional>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

// ~9 * 10 ^ 18
const ll LL_MAX = 9'223'372'036'854'775'807;

// ~2 * 10 ^ 9
const int MAX = 2'147'483'647;
const int MOD = 1'000'000'000 + 7;
// const int MOD2 = 998'244'353;

// const int N = 3e5 + 5;

/*
 * Problem takeways:
 *
 * We can figure out that it is always optimal to only have at most 1 + or - after some multiplication
 *
 * For example, whenever we have *++ or *--, that can be simplified into +* or -*.
 *
 * Thus, our DP is simple and for each i we only have to consider the previous and latter element.
 *
 *
 *
 *
 */


void solve() {
    ll n, x, y;
    cin >> n >> x >> y;

    vector<ll> dp;
    dp.reserve(2 * n + 1);
    dp.resize(2 * n + 1);

    fill(dp.begin(), dp.end(), LL_MAX);
    dp[0] = 0;

    for (ll i = 1; i <= 2 * n; i++) {
        dp[i] = dp[i - 1] + x;
        if (i % 2 == 0) {
            dp[i] = min(dp[i], dp[i / 2] + y);
            dp[i - 1] = min(dp[i - 1], dp[i] + x);
        }
    }

    cout << dp[n] << endl;
}

void multi_solve() {
    int t;
    cin >> t;

    while (t--) solve();
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
    // multi_solve();
}

