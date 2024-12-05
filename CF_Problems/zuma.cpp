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
    int n;
    cin >> n;

    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];

    vector<vector<int>> dp(n, vector<int>(n, MAX));

    for (int j = 0; j < n; j++) {
        dp[j][j] = 1;
        for (int i = j - 1; i >= 0; i--) {
            dp[i][j] = min(dp[i][j], 1 + dp[i + 1][j]);

            for (int k = j; k >= i + 1; k--) {
                if (c[i] != c[k]) continue;

                if (k == j) {
                    if (i + 1 == k) dp[i][j] = min(dp[i][j], 1);
                    else dp[i][j] = min(dp[i][j], dp[i + 1][k - 1]);
                }

                else if (i + 1 == k) {
                    dp[i][j] = min(dp[i][j], dp[k + 1][j] + 1);
                }

                else {
                    dp[i][j] = min(dp[i][j], dp[i + 1][k - 1] + dp[k + 1][j]);
                }
            }
        }
    }

    cout << dp[0][n - 1] << endl;
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


