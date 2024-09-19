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
 *
 *
 *
 *
 *
 */

const int MAX_LEN = 1e5 + 5;
int dists[3][MAX_LEN] {};

int dfs(vector<vector<int>>& g, int node, int parent, int len, int tp) {
    dists[tp][node] = len;

    int opt = -1;
    for (int child : g[node]) {
        if (child == parent) continue;
        int x = dfs(g, child, node, len + 1, tp);
        if (opt == -1 || dists[tp][x] > dists[tp][opt]) opt = x;
    }

    return opt == -1 ? node : opt;
}


vector<int> parents;

void make_set(int v) {
    parents[v] = v;
}

int find_set(int v) {
    if (v == parents[v]) return v;
    return parents[v] = find_set(parents[v]);
}

void union_sets(int a, int b, int& comps) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        parents[b] = a;
        comps--;
    }
}

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> g(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    int node1 = dfs(g, 0, -1, 0, 0);

    int node2 = dfs(g, node1, node1, 0, 1);

    dfs(g, node2, node2, 0, 2);

    vector<int> dnode(n, 0);
    vector<int> mdist(n, 0);

    vector<array<int, 3>> a(n);

    for (int i = 0; i < n; i++) {
        if (dists[1][i] > dists[2][i]) {
            dnode[i] = node1;
        } else dnode[i] = node2;

        mdist[i] = max(dists[1][i], dists[2][i]);

        a[i] = {i, dnode[i], mdist[i]};
    }

    sort(a.begin(), a.end(), [](auto& l, auto& r) {
        return l[2] > r[2];
    });

    parents.reserve(n);
    parents.resize(n);
    for (int i = 0; i < n; i++) make_set(i);

    vector<int> ans;

    int j = 0;
    int comps = n;

    for (int k = n; k >= 1; k--) {

        while (j < n && a[j][2] >= k) {
            union_sets(a[j][0], a[j][1], comps);
            j++;
        }

        ans.push_back(comps);
    }

    string s = to_string(ans.back());
    for (int i = ans.size() - 2; i >= 0; i--) s += " " + to_string(ans[i]);

    cout << s << endl;

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

