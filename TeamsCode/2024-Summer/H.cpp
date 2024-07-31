// #include <cstdio>

#include <deque>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <cmath>
#include <algorithm>

#define popcount    __builtin_popcount
#define popcount_ll __builtin_popcountll
#define lsb         __builtin_ctz
#define lsb_ll      __builtin_ctzll
#define msb         __builtin_clz
#define msb_ll      __builtin_clzll
#define parity      __builtin_parity

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

const ll LL_MAX = 9223372036854775807;
const int MAX = 2147483647;
const int CSES_MOD = 1'000'000'000 + 7;


void solve() {
    string as;
    string bs;

    cin >> as >> bs;

    int n = as.size(), m = bs.size();
    vector<int> a(n);
    vector<int> b(m);
    for (int i = 0; i < n; i++) a[i] = as[i] - '0';
    for (int i = 0; i < m; i++) b[i] = bs[i] - '0';

    vector<vector<ll>> dp(n + 1, vector<ll>(4, 0));

    int num_remove = n <= m ? 0 : (n - m);
    int start_rem = 0;

    for (int i = 0; i < 4; i++) {
        if (a[i] <= b[i]) break;
        start_rem++;
    }

    for (int i = start_rem; i < n; i++) {
        int j = 0;
        for (; j <= min((i - start_rem), 3); j++) {
            if (j < max(i - 4, 0)) {
                if (i != 0) dp[i][j] = dp[i - 1][j];
                continue;
            }

            if (j == 0) {
                dp[i][j] = a[i] <= b[j] ? 1 : 0;
                if (i != 0) dp[i][j] += dp[i - 1][j];
                cout << i << " " << j << " " << dp[i][j] << endl;
                continue;
            }

            if (a[i] > b[j]) dp[i][j] = 0;
            else if (i != 0) dp[i][j] = dp[i - 1][j - 1];
            if (i != 0) dp[i][j] += dp[i - 1][j];

            cout << i << " " << j << " " << dp[i][j] << " " << dp[i - 1][j] << " " << dp[i - 1][j - 1] << endl;
        }

        /*
        if (j == 4 && ) {
            for (int c = i + 1; c < n; c++) {

            }
        }
         */
    }

    for (int i = n; i >= 0; i--) {
        if (dp[3][i] != 0) {
            cout << dp[3][i] << endl;
            break;
        }
    }




}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // solve();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}