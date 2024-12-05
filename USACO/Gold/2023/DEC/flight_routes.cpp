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

    vector<vector<int>> parity(n, vector<int>(n));

    vector<vector<bool>> edge(n, vector<bool>(n, false));

    for (int i = 0; i < n - 1; i++) {
        string s;
        cin >> s;

        for (int j = i + 1; j < n; j++) {
            if (s[j - (i + 1)] == '0') {
                parity[i][j] = 0;
            } else parity[i][j] = 1;
        }
    }


    vector<vector<ll>> cnts(n, vector<ll>(n, 0));

    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            for (int c = i + 1; c < j; c++) {
                if (edge[i][c]) cnts[i][j] += cnts[c][j];
                cnts[i][j] %= 2;
            }

            if (parity[i][j] != (cnts[i][j] % 2)) {
                edge[i][j] = true;
                cnts[i][j]++;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // cout << i + 1 << " " << j + 1 << " " << cnts[i][j] << endl;
            // if (edge[i][j]) cout << "EDGE " << i + 1 << " " << j + 1 << endl;
            ans += edge[i][j];
        }
    }

    cout << ans << endl;
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


