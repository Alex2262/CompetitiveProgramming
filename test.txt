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
const ll MOD = 1'000'000'000 + 7;
// const ll MOD = 998'244'353;


/*
 *
 *
 *
 */


void solve() {
    int n;
    cin >> n;


    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];


    double p = 1.0 / n;
    double np = 1.0 - p;


    int sum = accumulate(a.begin(), a.end(), 0);

    double dp[n + 1][n][5];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int c = 0; c < 5; c++) {
                dp[i][j][c] = 1;
            }
        }
    }

    for (int j = 0; j < n; j++) dp[0][j][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int c = 0; c <= 3; c++) {
                // dp[i + 1][j][c] += dp[i][j][c];
                if (dp[i][j][c] == 0) continue;
                if (c >= a[j]) continue;

                dp[i + 1][j][c + 1] += p * dp[i][j][c];
                dp[i + 1][j][c] += np * dp[i][j][c];
                // cout << "HOLA " << i + 1 << " " << j << " " << c + 1 << " " << dp[i + 1][j][c + 1] << " " << dp[i][j][c] << endl;
            }

            for (int c = 0; c < 4; c++) {
                cout << fixed << " " << setprecision(12) << i + 1 << " " << j << " " << c << " " << dp[i + 1][j][c] << endl;
            }
        }
    }

    double ans = 0;

    for (int j = 0; j < n; j++) {
        ans += n * dp[n][j][a[j]];
    }

    cout << fixed << setprecision(12) << ans << endl;

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


