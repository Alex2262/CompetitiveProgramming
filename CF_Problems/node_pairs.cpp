#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

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
 */



void solve() {
    int p;
    cin >> p;

    ll n = 2 * sqrt(p) + 2;

    vector<pll> dp(p + 1, {-1, LL_MAX});
    dp[0] = {0, 0};

    for (int j = 0; j < p; j++) {
        if (dp[j].first == -1 || dp[j].second == LL_MAX) continue;

        for (int i = 2; i <= n; i++) {
            ll add = i * (i - 1) / 2;
            if (j + add > p) break;

            ll next1 = dp[j].first + dp[j].second * i;
            ll next2 = dp[j].second + i;

            if (next2 < dp[j + add].second || (next2 == dp[j + add].second && next1 > dp[j + add].first)) {
                dp[j + add].first = next1;
                dp[j + add].second = next2;
            }
        }
    }

    cout << dp[p].second << " " << dp[p].first << endl;
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
}

