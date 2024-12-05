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
    string a, b;
    cin >> a >> b;

    int n = b.size();
    int red = n - a.size();

    vector<int> digb(n);
    vector<int> diga(n);

    for (int i = 0; i < n; i++) {
        digb[i] = b[i] - '0';
        diga[i] = i < red ? 0 : a[i - red] - '0';
    }

    // restricting
    vector<bool> rb(n, false);
    for (int i = 1; i < n; i++) {
        if (diga[i - 1] == digb[i - 1]) rb[i] = true;
        if (i > 1 && !rb[i - 1]) rb[i] = false;
    }

    ll dp[n][10][3][2];
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < 10; j++) {
            for (ll c = 0; c < 3; c++) {
                dp[i][j][c][0] = 0;
                dp[i][j][c][1] = -1;
            }
        }
    }

    for (ll j = diga[0] + 1; j < digb[0]; j++) {
        dp[0][j][0][0] = max(j, 1LL);
    }

    dp[0][digb[0]][1][0] = max(digb[0], 1);
    // dp[0][diga[0]][1] = max(diga[0], 1);

    dp[0][diga[0]][2][0] = max(diga[0], 1);
    // dp[0][digb[0]][2] = max(digb[0], 1);

    for (ll i = 1; i < n; i++) {
        for (ll j = 0; j < 10; j++) {
            for (ll c = 0; c < 10; c++) {

                ll next0 = dp[i - 1][c][0][0] * j;
                ll next1 = dp[i - 1][c][1][0] * j;
                ll next2 = dp[i - 1][c][2][0] * j;

                if (j == 0 && c == 0) {
                    if (dp[i - 1][c][0][0] == 1LL) next0 = 1LL;
                    if (dp[i - 1][c][1][0] == 1LL) next1 = 1LL;
                    if (dp[i - 1][c][2][0] == 1LL) next2 = 1LL;
                }

                if (next0 > dp[i][j][0][0]) {
                    dp[i][j][0][0] = next0;
                    dp[i][j][0][1] = c;
                }

                if (j >= digb[i]) {
                    if (j == digb[i]) {
                        if (next1 > dp[i][j][1][0]) {
                            dp[i][j][1][0] = next1;
                            dp[i][j][1][1] = c;
                        }
                    }
                }

                else if (!rb[i]) {
                    if (next1 > dp[i][j][0][0]) {
                        dp[i][j][0][0] = next1;
                        dp[i][j][0][1] = c;
                    }
                }

                if (j <= diga[i]) {
                    if (j == diga[i]) {
                        if (next2 > dp[i][j][2][0]) {
                            dp[i][j][2][0] = next2;
                            dp[i][j][2][1] = c;
                        }
                    }
                }

                else if (!rb[i]) {
                    if (next2 > dp[i][j][0][0]) {
                        dp[i][j][0][0] = next2;
                        dp[i][j][0][1] = c;
                    }
                }

                if (j > diga[i] && j < digb[i]) {
                    if (next1 > dp[i][j][0][0]) {
                        dp[i][j][0][0] = next1;
                        dp[i][j][0][1] = c;
                    }

                    if (next2 > dp[i][j][0][0]) {
                        dp[i][j][0][0] = next2;
                        dp[i][j][0][1] = c;
                    }
                }
            }
        }
    }

    ll mx = 0;
    ll type = 0;
    ll best = 0;
    ll next = 0;

    for (ll j = 0; j < 10; j++) {
        for (ll c = 0; c < 3; c++) {
            if (dp[n - 1][j][c][0] > mx) {
                mx = dp[n - 1][j][c][0];
                best = j;
                next = dp[n - 1][j][c][1];
                type = c;
            }
        }
    }

    if (mx == 0) {
        cout << b << endl;
        return;
    }

    string s;
    s += to_string(best);

    for (ll i = n - 2; i >= 0; i--) {

        mx /= best;
        best = 0;

        for (ll c = 0; c < 3; c++) {
            if (c == type || type == 0) {
                if (dp[i][next][c][0] == mx) {
                    type = c;
                    best = next;
                    next = dp[i][next][c][1];
                    break;
                }
            }
        }

        s += to_string(best);
    }

    reverse(s.begin(), s.end());
    // cout << s << endl;
    ll ans = stoll(s);

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

