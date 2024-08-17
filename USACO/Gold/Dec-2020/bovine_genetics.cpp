
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
// const int MOD = 1'000'000'000 + 7;
const int MOD2 = 998'244'353;

/*
 *
 *
 *
 */

void solve() {
    string s;
    cin >> s;

    int n = s.size();
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        if (s[i] == 'A') a[i] = 0;
        else if (s[i] == 'G') a[i] = 1;
        else if (s[i] == 'C') a[i] = 2;
        else if (s[i] == 'T') a[i] = 3;
        else a[i] = 4;
    }

    ll dp[n + 1][4][4];
    for (int i = 0; i <= n; i++) {
        for (int l = 0; l < 4; l++) {
            for (int r = 0; r < 4; r++) dp[i][l][r] = 0;
        }
    }


    for (int i = 1; i <= n; i++) {
        int right_element = a[i - 1];
        vector<int> possible_right = {right_element};
        if (right_element == 4) possible_right = {0, 1, 2, 3};

        for (int pr : possible_right) {
            for (int j = i - 1; j >= 0; j--) {
                vector<int> possible_left = {a[j]};
                if (a[j] == 4) {
                    if (j == i - 1) possible_left = {pr};
                    else possible_left = {0, 1, 2, 3};
                }

                for (int pl : possible_left) {

                    // cout << right_element << " " << a[j] << endl;
                    // cout << j << " " << i << " " << pl << " " << pr << endl;
                    if (j == 0) {
                        dp[i][pl][pr] += 1;
                        continue;
                    }

                    vector<int> possible_end = {a[j - 1]};
                    if (a[j - 1] == 4) possible_end = {0, 1, 2, 3};

                    for (int pe : possible_end) {
                        vector<int> possible_start = {0, 1, 2, 3};
                        for (int ps : possible_start) {
                            if (ps != pr) continue;
                            dp[i][pl][pr] += dp[j - 1][pl][pe] + 1;
                        }
                    }
                }
            }
        }

    }

    ll ans = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ans += dp[n][i][j];
        }
    }

    cout << ans << endl;
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

