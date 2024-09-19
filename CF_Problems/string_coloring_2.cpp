#pragma GCC optimize("O3,unroll-loops")
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
const int MOD = 1'000'000'000 + 7;
// const int MOD2 = 998'244'353;

// const int N = 3e5 + 5;

/*
 * This is a nice problem.
 *
 * We have to think wider and outside the box in order to solve this problem. We need to realize that the answer
 * is the longest decreasing sequence inside the string. Why? Just think about if we have
 *
 * d > c > b > a as the longest then that definitely makes sense. All other sequences we know must be shorter,
 * so they can all be colored in less or same number of colors.
 *
 * Ultimately, our reconstruction is then that the color of the letter at this place is the number of colors
 * needed at this index, which is the longest decreasing subsequence ending at this index.
 *
 *
 *
 *
 */

void dfs(vector<vector<int>>& g, vector<bool>& visited, vector<int>& colors, int node, bool& works) {

    visited[node] = true;

    for (int child : g[node]) {
        if (colors[child] == colors[node]) {
            works = false;
            return;
        }

        if (visited[child]) continue;

        colors[child] = colors[node] ^ 1;
        dfs(g, visited, colors, child, works);
    }
}


void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    vector<int> maxdp(26, 0);
    vector<int> dp(n, 1);

    for (int i = 0; i < n; i++) {
        for (int c = 25; c > s[i] - 'a'; c--) {
            dp[i] = max(dp[i], maxdp[c] + 1);
        }

        maxdp[s[i] - 'a'] = max(maxdp[s[i] - 'a'], dp[i]);
    }

    cout << *max_element(dp.begin(), dp.end()) << endl;

    string res;
    for (int i = 0; i < n; i++) res += to_string(dp[i]) + " \n"[i == n - 1];

    cout << res;
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

    // ios_base::sync_with_stdio(false);
    // cin.tie(nullptr);

    solve();
    // multi_solve();
}

