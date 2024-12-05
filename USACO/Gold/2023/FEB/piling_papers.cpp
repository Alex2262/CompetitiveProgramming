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
 * Observations:
 *
 * The construction for each possible number from left to right.
 * Let's just assume for sake of simplicity our pages are 1, 2, 3, 4, 5
 *
 * We always need to go from some number (or nothing) --> 1 --> some other number (or nothing)
 *
 * valid examples:
 * 5 4 3 2 1
 * 5 1 2 3 4
 * 5 3 2 1 4
 * 1 2 3 4 5
 *
 *
 * 5 3 1 2 4
 * 5 2 1 3 4
 * 4 2 1 3 5
 * 3 2 1 4 5
 *
 * invalid:
 * 1 4 2 3 5
 *
 * in other words, it has one singular minima at ?
 *
 * what if we DP based on the current range of digit places covered?
 *
 * -----
 *
 * Our final solution was O(n^2 * m^2 * 9)
 * so O(n^2 * m^2)
 *
 * where m = log_10(B)
 *
 * so O(n^2 * log_10(B))
 *
 * ----- Problem takeaways -----
 *
 * We got this problem on our own!
 *
 * The big things we had to notice were
 *
 * 1. we need to do DP based on the range of digits that the number covers,
 * so that when we put a paper on top or below the stack, then for a range [i, j], we can test
 * a new number at i - 1 or j + 1.
 *
 * 2. we need a dimension with 3 values that determines if we are <, > or = to our upperbound
 * (same with our lowerbound)
 *
 * Then, with both of these, our transitions aren't terrible.
 *
 * Things that could have made this solution much easier:
 *
 * recognize that we only needed O(n ...) not O(n^2 ...) since we could do prefix sums on the counts,
 * instead of storing each unique range of papers and their own counts.
 *
 * The biggest takeaway that we should have noticed though, is that this would have been much simpler if we
 * just did DP up to upperbound B, then subtracted the answer based on DP up to upperbound A - 1.
 *
 * This would have made my life and the transitions way easier, since you wouldn't actually have to account for any
 * lowerbound.
 */



/*
ll rec(vector<int>& d, int n, int l, int r, int fix) {
    if (r == n) return 0;


    int curr = d[r];


}
 */

void add(ll& entry, ll amt) {
    entry = (entry + amt) % MOD;
}

void solve() {
    int n;
    cin >> n;

    string a, b;
    cin >> a >> b;

    vector<int> d(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }

    int m = b.size();
    int ma = a.size();

    vector<int> ad(m, 0);
    vector<int> bd(m, 0);

    int asub = b.size() - a.size();

    for (int i = 0; i < m; i++) {
        bd[i] = b[i] - '0';
        ad[i] = (i < asub ? 0 : a[i - asub] - '0');
    }

    // == count
    // 1: l
    // 2: r
    // 3: left digit place
    // 4: right digit place
    // 5: 0 --> curr < b
    //    1 --> curr > b
    //    2 --> curr = b
    // 6: 0 --> curr > a
    //    1 --> curr < a
    //    2 --> curr = a

    ll ans[n][n];

    for (int l = 0; l < n; l++) {
        for (int r = 0; r < n; r++) {
            ans[l][r] = 0;
        }
    }

    for (int l = 0; l < n; l++) {

        ll dp[n][m][m][3][3];
        for (int r = 0; r < n; r++) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < m; j++) {
                    for (int c = 0; c < 3; c++) {
                        for (int k = 0; k < 3; k++) {
                            dp[r][i][j][c][k] = 0;
                        }
                    }
                }
            }
        }

        for (int r = l; r < n; r++) {

            for (int i = 0; i < m; i++) {
                int type_b = d[r] > bd[i];
                int type_a = d[r] < ad[i];
                if (d[r] == bd[i]) type_b = 2;
                if (d[r] == ad[i]) type_a = 2;

                add(dp[r][i][i][type_b][type_a], 2);
            }

            if (r == l) goto update;

            for (int i = 0; i < m; i++) {

                for (int j = i; j < m; j++) {

                    int curr = d[r];

                    for (int c = 0; c < 3; c++) {
                        for (int k = 0; k < 3; k++) {
                            add(dp[r][i][j][c][k], dp[r - 1][i][j][c][k]);
                        }
                    }

                    if (i > 0) {
                        int type_b = curr > bd[i - 1];
                        int type_a = curr < ad[i - 1];

                        if (curr == bd[i - 1]) type_b = 2;
                        if (curr == ad[i - 1]) type_a = 2;

                        for (int c = 0; c < 3; c++) {
                            for (int k = 0; k < 3; k++) {
                                int t1 = c;
                                int t2 = k;

                                if (c == 0 && type_b == 1) t1 = 1;
                                if (c == 1 && type_b == 0) t1 = 0;
                                if (c == 2) t1 = type_b;

                                if (k == 0 && type_a == 1) t2 = 1;
                                if (k == 1 && type_a == 0) t2 = 0;
                                if (k == 2) t2 = type_a;

                                add(dp[r][i - 1][j][t1][t2], dp[r - 1][i][j][c][k]);
                            }
                        }
                    }

                    if (j < m - 1) {
                        int type_b = curr > bd[j + 1];
                        int type_a = curr < ad[j + 1];

                        if (curr == bd[j + 1]) type_b = 2;
                        if (curr == ad[j + 1]) type_a = 2;

                        for (int c = 0; c < 3; c++) {
                            for (int k = 0; k < 3; k++) {
                                int t1 = c;
                                int t2 = k;

                                if (c == 2) t1 = type_b;
                                if (k == 2) t2 = type_a;

                                add(dp[r][i][j + 1][t1][t2], dp[r - 1][i][j][c][k]);
                            }
                        }
                    }
                }
            }

            update:

            for (int i = m - ma; i >= 0; i--) {
                add(ans[l][r], dp[r][i][m - 1][0][0]);
                add(ans[l][r], dp[r][i][m - 1][0][2]);
                add(ans[l][r], dp[r][i][m - 1][2][0]);
                add(ans[l][r], dp[r][i][m - 1][2][2]);

                if (i > 0) {
                    add(ans[l][r], dp[r][i][m - 1][1][0]);
                    add(ans[l][r], dp[r][i][m - 1][1][2]);
                }
            }
        }
    }

    int q;
    cin >> q;
    for (int z = 0; z < q; z++) {
        int l, r;
        cin >> l >> r;
        l--, r--;

        cout << ans[l][r] << endl;
    }
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

