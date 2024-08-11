
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

/*
 * Problem takeaways:
 *
 * We have to realize that the number of rounds possible is very limited, it's like log(n) or something.
 * This means that we can obviously use DP to solve this problem, by testing using each number on each round with DFS.
 *
 * The issue I encountered was I found some brute force / kind of greedy DP approach but not a very sophisticated DP,
 * more bruteforce-ish approach, and then used the idea of the limited log(n) rounds to prove that this wouldn't TLE.
 *
 * The fact that this wouldn't TLE is correct, but I should have realized greedily minimizing each round wouldn't be
 * the best approach. Instead, in these cases, I should always look to doing DP, as it is basically foolproof.
 *
 *
 *
 */

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

void dfs(vector<vector<int>>& g, vector<vector<ll>>& dp, vector<ll>& a, int node, int parent) {

    for (int i = 0; i < 30; i++) {
        dp[node][i] = a[node] * i;
    }

    for (int child : g[node]) {
        if (child == parent) continue;
        dfs(g, dp, a, child, node);

        for (int i = 0; i < 30; i++) {
            ll mn = LL_MAX;
            for (int j = 0; j < 30; j++) {
                if (i == j) continue; // we obviously cant take parent & child in the same round
                mn = min(mn, dp[child][j]);
            }

            dp[node][i] += mn;
            // cout << node << " " << i << " " << dp[node][i] << endl;
        }
    }
}


void solve() {
    int n;
    cin >> n;

    vector<ll> a(n);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ans += a[i];
    }

    vector<vector<int>> g(n);

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;

        g[x].push_back(y);
        g[y].push_back(x);
    }

    vector<vector<ll>> dp(n, vector<ll>(30, 0));

    dfs(g, dp, a, 0, -1);

    ll best = LL_MAX;
    for (int i = 0; i < 30; i++) best = min(best, dp[0][i]);

    cout << ans + best << endl;

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

