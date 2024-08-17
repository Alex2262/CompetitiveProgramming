
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
#include <numeric>

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

// const int N = 3e5 + 5;

/*
 *
 *
 *
 *
 *
 */

int dfs(vector<int>& a, vector<int>& dp, vector<bool>& rec, int node, int n) {
    if (node >= n || node < 0) return dp[node] = 0;

    if (rec[node]) return -MAX;
    if (dp[node] != -1) return dp[node];

    rec[node] = true;
    int len = dfs(a, dp, rec, node + a[node], n) + 1;
    rec[node] = false;

    return dp[node] = len;
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> dp(n, -1);
    vector<bool> rec(n, false);

    vector<int> path;
    set<int> ps;


    ll ans = 0;

    for (int i = 0; i < n; i++) {
        dfs(a, dp, rec, i, n);

        if (i == 0 && dp[0] >= 0) {
            int count = 0;
            for (int j = 1; j < n; j++) {
                if (dp[j] == -1) count++;
            }

            // cout << "COUNT " << count << endl;
            ans += count * (2 * n + 1);
        }

        if (i == 0) {
            for (int j = 0; j < n; j++) {
                if (dp[j] != -1) {
                    path.push_back(j);
                    ps.insert(j);
                }
            }
        }
    }

    ll c = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] < 0) c++;
    }

    cout << "C: " << c << endl;
    for (int j = path.size() - 1; j >= 0; j--) {
        int i = path[j];
        bool works = dp[i] > 0;
        int red = works ? j + 1 : 0;

        cout << 2 * n + 1 - c - red << endl;
        // ans += (2 * n + 1 - c - red - works);

        ans += (2 * n + 1 - c - red);
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


    // solve();

    // /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    // */
}

