
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
#include <functional>

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


array<ll, 3> dfs(vector<vector<pii>>& g, vector<array<ll, 3>>& dp, int node) {

    array<ll, 3> res{};

    for (auto p : g[node]) {
        int child = p.first;
        int weight = p.second;

        array<ll, 3> c_res{};

        if (weight == 0) {
            res[2] = (res[2] + res[1]) % MOD2;
            res[0] = (res[0] + 1) % MOD2;
        }
        else if (weight == 1) res[1] = (res[1] + 1) % MOD2;

        if (dp[child][0] != -1) c_res = dp[child];
        else c_res = dfs(g, dp, child);

        res[2] = (res[2] + c_res[2]) % MOD2;
        res[2] = (res[2] + (res[1] * c_res[0]) % MOD2) % MOD2;

        res[0] = (res[0] + c_res[0]) % MOD2;
        res[1] = (res[1] + c_res[1]) % MOD2;
    }

    dp[node] = res;
    return res;
}

void solve() {
    int n;
    cin >> n;

    vector<vector<pii>> g(n);

    for (int i = 0; i < n; i++) {
        int s;
        cin >> s;

        for (int j = 0; j < s; j++) {
            int l, w;
            cin >> l >> w;
            l--;

            g[i].emplace_back(l, w);
        }
    }

    vector<array<ll, 3>> dp(n, {-1, -1, 0});

    dfs(g, dp, 0);

    cout << dp[0][2] << endl;
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

