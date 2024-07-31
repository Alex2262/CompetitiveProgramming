// #include <cstdio>

/*
 * Problem takeaways
 *
 * We must observe that we can simplify this problem statement into maximizing the number of distinct cakes
 * that Bob can eat. Then we subtract this from total amount of distinct cakes.
 *
 *
 */
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

    // Our dp is [i][j]
    // i represents the number of cakes we consider right now
    // j
    vector<vector<int>> dp(n + 1, vector<int>(n, 0));

    int m = cakes.size();
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            dp[i][j] = dp[i - 1][j];
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