// #include <cstdio>

/*
 * Problem takeaways:
 *
 * It is easy to see that we need a bipartite graph if we choose Bob, otherwise, choose Alice.
 *
 * The hard part is the interactive sequence for Bob, where we need to ensure we actually split the colors into
 * the two respective parts and take from each one, since Alice doesn't have to play "optimally" and can choose
 * whatever 2 colors she wants, forcing us not to be able to simply DFS greedily.
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
const int MOD = 1'000'000'000 + 7;

bool dfs(vector<vector<int>>& g, vector<int>& colors, int node, int parent, int len) {
    if (colors[node] != -1) {
        return (colors[node] ^ len) & 1;
    }

    colors[node] = len & 1;

    bool nonbi = false;
    for (int child : g[node]) {
        if (child == parent) continue;
        nonbi |= dfs(g, colors, child, node, len + 1);
    }

    return nonbi;
}

void solve() {
    int n, m;
    cin >> n >> m;

    if (n == -1 || m == -1) return;

    vector<vector<int>> g(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> colors(n, -1);
    bool nonbi = dfs(g, colors, 0, -1, 0);

    if (nonbi) {
        cout << "Alice" << endl;
        for (int i = 0; i < n; i++) {
            cout << "1 2" << endl;
            int a, b;
            cin >> a >> b;

            if (a == -1 || b == -1) return;
        }
    }

    else {
        cout << "Bob" << endl;

        queue<int> black;
        queue<int> red;
        for (int i = 0; i < n; i++) {
            if (colors[i] == 0) black.push(i + 1);
            else red.push(i + 1);
        }

        for (int i = 0; i < n; i++) {
            int a, b;
            cin >> a >> b;
            if (a == -1 || b == -1) return;

            int c = 0;
            bool use_black = true;
            if (a == 1 || b == 1) {
                if (!black.empty()) c = 1;
                else {
                    use_black = false;
                    c = a == 1 ? b : a;
                }
            } else {
                if (!red.empty()) {
                    use_black = false;
                    c = 2;
                }
                else c = a == 2 ? b : a;
            }

            if (use_black) {
                cout << black.front() << " " << c << endl;
                black.pop();
            } else {
                cout << red.front() << " " << c << endl;
                red.pop();
            }


        }
    }
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);

    // solve();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}