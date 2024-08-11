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


const int N = 3e5 + 5;
int tree[N * 2];
int tree_n;

// BUILD TREE
// O(n)
// Note that:
// 1. i << 1     == i * 2
// 2. i << 1 | 1 == i * 2 + 1
void build() {
    for (int i = tree_n - 1; i > 0; i--) tree[i] = min(tree[i << 1], tree[i << 1 | 1]);
}

// MODIFY TREE (single point)
// O(log(n))
// Note that:
// p ^ 1 ensures we add both child nodes
void modify_point(int p, int value) {
    p += tree_n;
    tree[p] = value;
    for (; p > 1; p >>= 1) tree[p >> 1] = min(tree[p], tree[p ^ 1]);
}

// QUERY (range)
// O(log(n))
// sum on interval [l, r)
int query_range(int l, int r) {
    l += tree_n, r += tree_n;
    int res = MAX;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            res = min(res, tree[l]);
            l++;
        }
        if (r & 1) {
            r--;
            res = min(res, tree[r]);
        } // Remember that r is the excluded bound
    }

    return res;
}


void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];

    tree_n = n + 1;
    vector<int> dp(tree_n, MAX);
    dp[0] = 0;

    for (int i = 0; i < tree_n; i++) {
        tree[i + tree_n] = dp[i];
    }

    build();

    // cout << "Q " << query_range(1, tree_n) << endl;

    queue<int> q;

    for (int i = 1; i < tree_n; i++) {
        q.push(i);
    }

    vector<bool> visited(tree_n, false);
    visited[0] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        visited[curr] = true;

        int depth = curr + b[curr - 1];

        // cout << curr << " " << depth << " " << a[depth - 1] << endl;

        int l = max(depth - a[depth - 1], 0);
        int r = depth;

        int best = query_range(l, r);
        // cout << "SEG " << l << " " << r << " " << best << endl;

        if (best == MAX) {
            if (visited[curr]) continue;

            q.push(curr);
            continue;
        }

        dp[curr] = best + 1;

        // cout << "DP " << dp[curr] << endl;
        modify_point(curr, dp[curr]);
    }

    if (dp[n] == MAX) {
        cout << -1 << endl;
        return;
    }

    // cout << "WHAT" << endl;

    cout << dp[n] << endl;

    int curr = n;
    int ops = dp[n];

    vector<int> path;
    while (ops) {

        curr += b[curr - 1];

        // cout << ops << " " << curr << endl;

        for (int i = 1; i <= a[curr - 1]; i++) {
            if (dp[curr - i] == ops - 1) {
                curr = curr - i;
                break;
            }
        }

        // cout << curr << endl;

        ops--;

        path.push_back(curr);
    }

    string s = to_string(path[0]);
    for (int i = 1; i < path.size(); i++) s += " " + to_string(path[i]);

    cout << s << endl;


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
