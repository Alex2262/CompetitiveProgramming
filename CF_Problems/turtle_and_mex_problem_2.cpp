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
 * Problem takeaways:
 *
 * We are able to come up with the fact that this has to do with graphs, and forming edges between mex and mx.
 *
 * However, the issue with this problem came in implementing a good, clean solution that made sense and was fast enough.
 *
 * In contest, I tried doing DFS and DP in the DFS, but this was too convoluted and too slow.
 * What I should have realized, is that we can simply do DP by going from large --> small on mex values,
 * and storing the maximum possible that we can achieve in here.
 *
 * During a contest, make sure to think carefully about how to implement solutions cleanly.
 *
 */


void solve() {
    int n;
    cin >> n;

    ll m;
    cin >> m;

    ll ans = m * (m + 1) / 2;

    vector<pii> edges;
    int mx2 = 0;
    int mxx = 0;

    for (int i = 0; i < n; i++) {
        int l;
        cin >> l;

        set<int> a;

        for (int j = 0; j < l; j++) {
            int t;
            cin >> t;
            a.insert(t);
        }

        int mex = -1;
        int mx = 0;

        for (int j = 0; j <= l + 2; j++) {
            if (a.find(j) == a.end()) {
                if (mex != -1) {
                    mx = j;
                    break;
                }

                mex = j;
                continue;
            }
        }

        edges.emplace_back(mex, mx);
        mx2 = max(mx2, mx);
        mxx = max(mxx, mex);
    }

    vector<int> cnt(mx2 + 1, 0);

    for (auto e : edges) {
        cnt[e.first]++;
    }

    vector<vector<int>> g(mx2 + 1);

    for (auto e : edges) {
        g[e.first].push_back(e.second);
    }

    vector<int> dp(mx2 + 1, 0);

    for (int x = mx2; x >= 0; x--) {
        dp[x] = x;
        for (auto y : g[x]) {
            dp[x] = max(dp[x], dp[y]);
        }

        if (cnt[x] > 1) {
            mxx = max(mxx, dp[x]);
        }
    }

    ll rem = 0;

    ll num = min<ll>(m, mxx);

    for (int i = 0; i <= min<ll>(m, mx2); i++) {
        if (dp[i] <= mxx) continue;

        ans -= i;
        ans += dp[i];

        if (i <= num) {
            rem++;
            ans += i; // we will remove it later again
        }
    }

    ans -= num * (num + 1) / 2;
    ans += (num + 1 - rem) * mxx;

    cout << ans << endl;
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

    // solve();
    multi_solve();
}

