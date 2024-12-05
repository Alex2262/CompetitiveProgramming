#pragma GCC optimize("O2,unroll-loops")
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
// const ll MOD = 1'000'000'000 + 7;
const ll MOD2 = 998'244'353;


/*
 *
 *
 *
 */


void solve() {
    int n, p, k;
    cin >> n >> p >> k;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<vector<ll>> s(n, vector<ll>(p));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            cin >> s[i][j];
        }
    }

    ll sum = accumulate(a.begin(), a.end(), 0LL);

    const int fm = (1 << 7);

    // the best we can achieve such that
    // dp[i][j]
    // where i represents the subset of positions filled of fm
    // j is the index that is not included in the subset
    // so we basically want to find the best subset i such that we don't include j

    vector<vector<ll>> dp(fm, vector<ll>(n));

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < fm; j++) {
            for (int c = 0; c < 7; c++) {
                if (!(j & (1 << c))) continue;
                // pull DP transitions


            }
        }
    }
}

void multi_solve() {
    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        solve();
    }
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


