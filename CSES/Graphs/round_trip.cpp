
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

int dfs(vector<vector<int>>& g, vector<int>& parents, vector<bool>& rec, int node) {

    int found = -1;
    for (int child : g[node]) {
        if (child == parents[node]) continue;

        rec[node] = true;

        if (rec[child]) {
            found = child;
            parents[child] = node;
            rec[node] = false;
            return found;
        }

        if (parents[child] != -1) continue;
        parents[child] = node;

        found = max(found, dfs(g, parents, rec, child));
        rec[node] = false;

        if (found != -1) return found;
    }

    return found;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> parents(n, -1);
    vector<bool> rec(n, false);

    int found = -1;
    for (int i = 0; i < n; i++) {
        if (parents[i] != -1) continue;

        found = dfs(g, parents, rec, i);
        if (found != -1) break;
    }


    if (found == -1) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }

    int node = found;
    vector<int> path;
    path.push_back(node + 1);

    // cout << "FOUND " << found << endl;

    while (parents[node] != MAX) {
        // cout << node << endl;

        node = parents[node];
        path.push_back(node + 1);

        if (node == found) break;
    }

    cout << path.size() << endl;
    string s = to_string(path.back());
    for (int i = path.size() - 2; i >= 0; i--) s += " " + to_string(path[i]);

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

