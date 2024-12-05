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
const ll MOD = 998'244'353;


/*
 *
 *
 *
 */


void solve() {
    string s;
    cin >> s;

    vector<int> w;
    for (int i = 0; i < 10; i++) {
        if (s[i] == '1') w.push_back(i + 1);
    }

    int m;
    cin >> m;

    if (m == 1) {
        if (w.empty()) cout << "NO" << endl;
        else {
            cout << "YES" << endl;
            cout << to_string(w[0]) << endl;
        }

        return;
    }

    int n = w.size();

    bool dp[m][10][10];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                dp[i][j][k] = false;
            }
        }
    }

    for (int next : w) {
        if (next >= 10) continue;
        dp[0][next - 1][next] = true;
    }

    for (int i = 1; i < m; i++) {
        for (int next : w) {
            for (int prev : w) {
                if (next == prev) continue;
                for (int diff = 0; diff < 10; diff++) {
                    if (!dp[i - 1][prev - 1][diff]) continue;
                    if (next <= diff) continue;
                    int nd = next - diff;
                    if (nd >= 10) continue;

                    dp[i][next - 1][nd] |= true;
                }
            }
        }
    }

    int p = -1;
    int d = -1;
    for (int prev : w) {
        for (int diff = 0; diff < 10; diff++) {
            if (dp[m - 1][prev - 1][diff]) {
                p = prev;
                d = diff;
                break;
            }
        }
    }

    if (p == -1) {
        cout << "NO" << endl;
        return;
    }

    vector<int> ans(m);
    ans[m - 1] = p;
    for (int i = m - 2; i >= 0; i--) {
        int nd = p - d;
        int next = 0;
        for (int prev : w) {
            if (prev == p) continue;
            if (!dp[i][prev - 1][nd]) continue;

            next = prev;
            break;
        }

        p = next;
        d = nd;
        ans[i] = p;
    }

    cout << "YES" << endl;

    string res;
    for (int i = 0; i < m; i++) res += to_string(ans[i]) + " \n"[i == m - 1];

    cout << res;
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


