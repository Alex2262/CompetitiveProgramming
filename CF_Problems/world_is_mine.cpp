// #include <cstdio>

/*
 * Problem takeaways
 *
 * We must observe that we can simplify this problem statement into maximizing the number of distinct cakes
 * that Bob can eat. Then we subtract this from total amount of distinct cakes.
 *
 *
 * This problem was very challenging for me, for some reason.
 *
 * Once we know the greedy solution doesn't work, we should realize that this is DP.
 *
 * How can we use DP to solve this?
 *
 * We know the value we store in the DP must be the maximum amount we can achieve
 *
 * Well like every other type of problem where someone needs to choose an element to remove, so knapsack type
 * problem, our first index should obviously be considering taking the current element.
 *
 * So, i = Bob tries taking the current element, and the previous ones have already been dealt with.
 *
 * But this alone cannot solve us our problem.
 * We need a second index, j, that represents how many turns Bob has left to eat a certain cake.
 * We know for each new layer, bob is able to achieve the same thing as the previous layer with j + 1 since
 * there is an extra turn now.
 *
 * We can transition by saying that if we take the current cake for bob, he gets + 1 from the previous layer in which
 * we had j + cnt[i] remaining.
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

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> freq(n + 1, 0);
    for (int i = 0; i < n; i++) freq[a[i]]++;

    vector<int> cakes;
    for (int i = 0; i <= n; i++) {
        if (freq[i] == 0) continue;
        cakes.push_back(freq[i]);
    }

    int m = cakes.size();

    // Our dp is [i][j]
    // i represents the cake that we are trying to eat now
    // j is the remaining amount of cakes bob can eat (like individual count, not a full distinct cake)
    // dp[i][j] = num cakes that bob can remove

    vector<vector<int>> dp(m + 1, vector<int>(m + 1, -MAX));  //
    dp[0][0] = 0;

    int mx = 0;

    for (int i = 1; i <= m; i++) {

        for (int j = 0; j < m; j++) {
            // we must do j + 1 here since we know if bob had j remaining previously,
            // now at j + 1 remaining he can achieve the same result.
            // why? because we gave one more turn to alice, so bob gets + 1 to account for this.
            dp[i][j + 1] = max(dp[i][j + 1], dp[i - 1][j]);
        }

        for (int j = 0; j <= m - cakes[i - 1]; j++) {
            // transition
            dp[i][j] = max(dp[i][j], dp[i - 1][j + cakes[i - 1]] + 1);
            // cout << i << " " << j << " " << dp[i][j] << endl;
        }
    }

    for (int i = 0; i <= m; i++) mx = max(mx, dp[m][i]);

    cout << m - mx << endl;
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

