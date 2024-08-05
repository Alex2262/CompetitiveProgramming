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



const int N = 1e5 + 10;
int tree[N * 2];
int n;

// MODIFY TREE (range)
// O(log(n))
// [l, r)
void modify_range(int l, int r, int value) {
    l += n, r += n;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) tree[l++] += value;
        if (r & 1) tree[--r] += value;
    }
}

// PUSH
void push() {
    for (int i = 1; i < n; i++) {
        tree[i << 1] += tree[i];
        tree[(i << 1) | 1] += tree[i];
        tree[i] = 0;
    }
}


void LIS(vector<int>& a, vector<int>& lengths) {
    vector<int> dp(n + 1, 0);
    int curr_max = 0;

    for (int i = 0; i < n; i++) {
        int ind = upper_bound(dp.begin(), dp.begin() + curr_max + 1, a[i]) - dp.begin();

        dp[ind] = a[i];
        lengths[i] = ind;

        curr_max = max(curr_max, ind);
    }
}

void solve() {
    int m;
    cin >> m >> n;

    memset(tree, 0, sizeof(tree));

    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;

        // cout << l << " " << r << endl;
        modify_range(l, r + 1, 1);
    }

    push();
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = tree[n + i];

    // for (int i = 0; i < n; i++) cout << a[i] << endl;
    vector<int> forward(n, 0);
    LIS(a, forward);
    vector<int> backward(n, 0);
    reverse(a.begin(), a.end());
    LIS(a, backward);
    reverse(backward.begin(), backward.end());

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, forward[i] + (i == n - 1 ? 0 : backward[i + 1]));
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

