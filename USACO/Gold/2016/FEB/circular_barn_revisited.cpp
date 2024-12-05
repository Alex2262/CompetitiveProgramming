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


void solve() {

    freopen("cbarn2.in", "r", stdin);
    freopen("cbarn2.out", "w", stdout);

    int n, k;
    cin >> n >> k;

    vector<ll> r(n);
    for (int i = 0; i < n; i++) cin >> r[i];

    ll dp[n][n][k + 1];

    for (int start = 0; start < n; start++) {
        dp[start][start][0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= k; j++) {
                dp[start][i][j] = LL_MAX;
            }
        }
    }

    // dist = 1 * r[i] + 2 * r[i + 1] + 3 * r[i + 2] ...
    // dist =

    for (int start = 0; start < n; start++) {
        for (int j = 1; j <= k; j++) {
            for (int i = start + 1; i <= n + start; i++) {
                int ind = i % n;

                if (j == k && ind != start) continue;  // we must end on start to close the loop

                ll curr_score = 0;
                ll sum = 0;

                for (int c = i - 1; c >= start + j - 1; c--) {
                    int cind = c % n;

                    // cout << start << " " << i << " " << j << " " << c << " " << curr_score << endl;
                    // cout << "CIND " << dp[start][cind][j - 1] << endl;

                    if ((j == 1 && cind == start) || j > 1) {
                        // cout << "OK " << endl;
                        if (dp[start][cind][j - 1] != LL_MAX)
                            dp[start][ind][j] = min(dp[start][ind][j], dp[start][cind][j - 1] + curr_score);
                    }

                    curr_score += sum + r[cind];
                    sum += r[cind];
                }

                // cout << "DP " << start << " " << i << " " << j << " " << dp[start][ind][j] << endl;
            }
        }
    }

    ll ans = LL_MAX;

    for (int start = 0; start < n; start++) {
        // cout << start << " " << dp[start][start][k] << endl;
        ans = min(ans, dp[start][start][k]);
    }

    cout << ans << endl;
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

