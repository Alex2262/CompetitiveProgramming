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
 *
 *
 *
 *
 *
 */


void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    vector<ll> c(k), h(k);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }

    for (int i = 0; i < k; i++) cin >> c[i];
    for (int i = 0; i < k; i++) cin >> h[i];

    ll ans = 0;
    for (int i = 0; i < n; i++) ans += c[a[i]];

    vector<ll> dp(k + 1, -LL_MAX);
    dp[a[0]] = 0;

    ll best = 0;
    ll add = 0;

    for (int i = 1; i < n; i++) {
        ll val = max(best, dp[a[i]] + add + c[a[i]] - h[a[i]]);

        if (a[i] == a[i - 1]) {
            best += c[a[i]] - h[a[i]];
            add += c[a[i]] - h[a[i]];
        }

        dp[a[i - 1]] = max(dp[a[i - 1]], val - add);
        best = max(best, val);
    }

    cout << ans - best << endl;
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

    // solve();
    multi_solve();
}

