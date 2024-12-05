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
 *
 */


ll comp(ll u) {
    string us = to_string(u);
    int n = us.size();

    vector<int> d(n);
    for (int i = 0; i < n; i++) {
        d[i] = us[i] - '0';
    }


    ll dp[n][10][2][2];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            for (int c = 0; c < 2; c++) {
                dp[i][j][c][0] = 0;
                dp[i][j][c][1] = 0;
            }
        }
    }

    for (int j = 0; j < d[0]; j++) {
        dp[0][j][0][0] = j;
        dp[0][j][0][1] = 1;
    }

    dp[0][d[0]][1][0] = d[0];
    dp[0][d[0]][1][1] = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            for (int c = 0; c < 10; c++) {
                dp[i][j][0][0] += dp[i - 1][c][0][0] + dp[i - 1][c][0][1] * j;
                dp[i][j][0][1] += dp[i - 1][c][0][1];

                if (j >= d[i]) {
                    if (j == d[i]) {
                        dp[i][j][1][0] += dp[i - 1][c][1][0] + dp[i - 1][c][1][1] * j;
                        dp[i][j][1][1] += dp[i - 1][c][1][1];
                    }
                }

                else {
                    dp[i][j][0][0] += dp[i - 1][c][1][0] + dp[i - 1][c][1][1] * j;
                    dp[i][j][0][1] += dp[i - 1][c][1][1];
                }
            }
        }
    }

    ll ans = 0;
    for (int j = 0; j < 10; j++) {
        ans += dp[n - 1][j][0][0];
        ans += dp[n - 1][j][1][0];
    }

    return ans;
}

void solve() {
    ll a, b;
    cin >> a >> b;

    cout << comp(b) - comp(a - 1) << endl;
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

    multi_solve();
}

