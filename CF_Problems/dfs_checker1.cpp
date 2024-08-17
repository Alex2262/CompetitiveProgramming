
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

/*
 *
 *
 *
 */

void dfs(vector<vector<int>>& g, vector<int>& parents_dp, int node, int parent, int& order, int parent_order) {
    int curr_order = order;
    parents_dp[order] = parent_order;

    for (int child : g[node]) {
        if (child == parent) continue;
        order++;
        dfs(g, parents_dp, child, node, order, curr_order);
    }
}


int check_node(vector<vector<int>>& g, vector<int>& parents_dp, vector<int>& parent, vector<int>& perm, int pos, int n) {
    if (pos >= n) return 0;

    // cout << "CHECKING " << pos << endl;

    int curr_correct = 0;
    int node = perm[pos];

    if (pos == 0) return node == 0;

    if (perm[parents_dp[pos]] == parent[node]) curr_correct++;

    // check children
    /*
    if (check_child) {
        if (!g[perm[pos]].empty() && !child_pos[pos].empty()) {
            // cout << "CHILD " << child_pos[pos].size() << " " << pos << endl;
            if (perm[child_pos[pos][0]] == g[perm[pos]][0] || perm[child_pos[pos][0]] == g[perm[pos]][1]) curr_correct++;
            if (perm[child_pos[pos][1]] == g[perm[pos]][0] || perm[child_pos[pos][1]] == g[perm[pos]][1]) curr_correct++;
        }
    }
     */

    return curr_correct;
}

void solve() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> g(n);
    vector<int> parent(n);
    for (int i = 1; i < n; i++) {
        int a;
        cin >> a;
        a--;
        g[a].push_back(i);
        parent[i] = a;
    }

    vector<int> perm(n);
    for (int i = 0; i < n; i++) {
        cin >> perm[i];
        perm[i]--;
    }

    vector<int> parents_dp(n);
    vector<vector<int>> child_pos(n);

    int order = 0;
    dfs(g, parents_dp, 0, -1, order, -1);

    for (int i = 1; i < n; i++) child_pos[parents_dp[i]].push_back(i);

    int num_correct = 0;
    for (int i = 0; i < n; i++) {
        num_correct += check_node(g, parents_dp, parent, perm, i, n);
    }

    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;

        // cout << num_correct << endl;

        set<int> pos;
        pos.insert(x);
        pos.insert(y);

        for (int e : child_pos[x]) pos.insert(e);
        for (int e : child_pos[y]) pos.insert(e);

        for (int p : pos) num_correct -= check_node(g, parents_dp, parent, perm, p, n);

        int temp = perm[x];
        perm[x] = perm[y];
        perm[y] = temp;

        for (int p : pos) num_correct += check_node(g, parents_dp, parent, perm, p, n);
        num_correct = clamp(num_correct, 0, n);

        if (num_correct == n) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
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

