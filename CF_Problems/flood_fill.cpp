// #include <cstdio>

#include <deque>
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <cmath>
#include <algorithm>
#include <cstring>

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
// const int MOD = 1'000'000'000 + 7;
const int MOD2 = 998'244'353;


void solve() {
    int n;
    cin >> n;

    vector<int> temp(n);
    for (int i = 0; i < n; i++) {
        cin >> temp[i];
        temp[i]--;
    }

    vector<int> c;
    c.push_back(temp[0]);

    // string s = to_string(c.back());
    for (int i = 1; i < n; i++) {
        if (c.back() != temp[i]) {
            c.push_back(temp[i]);
            // s += " " + to_string(c.back());
        }
    }

    // cout << s << endl;

    n = c.size();

    vector<vector<int>> dp(n, vector<int>(n, MAX));

    for (int i = 0; i < n; i++) dp[i][i] = 0;

    for (int i = 0; i < n; i++) {
        // dp[i][0] = min(dp[i][0], )
        for (int j = i - 1; j >= 0; j--) {


            dp[i][j] = min(dp[i][j], dp[i][j + 1] + (c[j] != c[j + 1]));

            dp[i][j] = min(dp[i][j], dp[i - 1][j] + (c[j] != c[i]));


            // cout << i << " " << j << " " << dp[i][j] << endl;
        }
    }

    cout << dp[n - 1][0] << endl;
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

    /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
     */
}

