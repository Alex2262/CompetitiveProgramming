
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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


void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    set<int> start_divs, end_divs;

    int start = a[0][0], end = a[n - 1][m - 1];

    for (int i = 1; i <= sqrt(start); i++) {
        if (start % i == 0) {
            start_divs.insert(i);
            start_divs.insert(start / i);
        }
    }

    for (int i = 1; i <= sqrt(end); i++) {
        if (end % i == 0) {
            end_divs.insert(i);
            end_divs.insert(end / i);
        }
    }

    vector<int> divs;
    for (int e : start_divs) {
        if (end_divs.find(e) != end_divs.end()) {
            divs.push_back(e);
        }
    }

    sort(divs.begin(), divs.end(), greater<>());

    // for (int e : divs) cout << e << endl;

    bool dp[n][m];

    int best = 1;

    for (int div : divs) {
        memset(dp, false, sizeof(dp));

        dp[0][0] = true;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i > 0 && dp[i - 1][j]) dp[i][j] = true;
                if (j > 0 && dp[i][j - 1]) dp[i][j] = true;

                dp[i][j] &= (a[i][j] % div) == 0;
            }
        }

        if (dp[n - 1][m - 1]) {
            best = div;
            break;
        }
    }

    cout << best << endl;
}

int main() {

    /*
     * FAST IO
     * Remember to remove for interactive problems!!!
     * https://stackoverflow.com/questions/31162367/significance-of-ios-basesync-with-stdiofalse-cin-tienull
     */

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);


    // solve();

    // /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    // */
}

