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

    vector<ll> dp(k + 1, LL_MAX);
    dp[a[0]] = c[a[0]];

    for (int i = 1; i < n; i++) {
        vector<ll> next(k + 1, LL_MAX);
        for (int j = 0; j < k; j++) {
            if (dp[j] == LL_MAX) continue;
            next[j] = dp[j] + (a[i] == a[i - 1] ? h[a[i]] : c[a[i]]);
        }

        ll mn = LL_MAX;
        for (int j = 0; j < k; j++) mn = min(mn, dp[j]);

        if (dp[a[i]] != LL_MAX) next[a[i - 1]] = min(next[a[i - 1]], dp[a[i]] + h[a[i]]);
        next[a[i - 1]] = min(next[a[i - 1]], mn + c[a[i]]);

        dp = next;
    }


    ll mn = LL_MAX;
    for (int j = 0; j < k; j++) mn = min(mn, dp[j]);

    cout << mn << endl;
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

