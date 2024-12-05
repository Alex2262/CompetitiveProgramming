
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// ~9 * 10 ^ 18
const ll LL_MAX = 9'223'372'036'854'775'807;

// ~2 * 10 ^ 9
const int MAX = 2'147'483'647;
// const ll MOD = 1'000'000'000 + 7;
const ll MOD = 998'244'353;



/*
 *
 *
 *
 */


class DSU {

private:
    vector<int> parents;
    vector<int> sizes;

public:
    vector<map<int, int>> con;
    vector<multiset<int>> ms;

    DSU(int size) : parents(size), sizes(size + 1, 1), con(size), ms(size) {
        for (int i = 0; i < size; i++) {
            parents[i] = i;
            con[i][i] = 0;
            ms[i].insert(0);
        }
    }

    int find(int v) {
        if (v == parents[v]) return v;
        return parents[v] = find(parents[v]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;

        if (sizes[a] < sizes[b]) swap(a, b);
        parents[b] = a;
        sizes[a] += sizes[b];

        for (auto p : con[b]) {
            con[a][p.first] = p.second;
            ms[a].insert(p.second);
        }
    }

    int get_size(int node) {
        return sizes[find(node)];
    }
};

void dfs(vector<set<int>>& g, vector<int>& nodes, vector<bool>& vis, int node) {
    vis[node] = true;
    nodes.push_back(node);

    for (int child : g[node]) {
        if (vis[child]) continue;
        dfs(g, nodes, vis, child);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<set<int>> g(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        g[u].insert(v);
        g[v].insert(u);
    }

    DSU dsu = DSU(n);

    ll best = 0;
    vector<bool> vis(n, false);
    vector<bool> add(n, false);
    vector<int> conn(n, 0);
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;

        vector<int> nodes;
        priority_queue<pair<ll, int>> pq;

        dfs(g, nodes, vis, i);

        for (int node : nodes) {
            add[node] = false;
            conn[node] = 0;

            pq.push({g[node].size(), node});
        }

        while (!pq.empty()) {
            auto p = pq.top();
            pq.pop();

            int curr = p.second;

            if (add[curr]) continue;
            add[curr] = true;

            for (int child : g[curr]) {
                if (!add[child]) continue;
                dsu.unite(curr, child);
            }

            int par = dsu.find(curr);
            int amt = 0;
            for (int child : g[curr]) {
                if (!add[child]) {
                    conn[child]++;
                    ll weight = conn[child];
                    weight += g[child].size() * n;

                    pq.push({weight, child});
                    continue;
                }
                dsu.ms[par].erase(dsu.ms[par].find(dsu.con[par][child]));
                dsu.con[par][child]++;
                dsu.ms[par].insert(dsu.con[par][child]);
                amt++;
            }

            dsu.ms[par].erase(dsu.ms[par].find(dsu.con[par][curr]));
            dsu.con[par][curr] += amt;
            dsu.ms[par].insert(dsu.con[par][curr]);

            // cout << curr << " " << endl;

            best = max<ll>(best, dsu.get_size(curr) * *dsu.ms[par].begin());
        }

        /*
        while (!pq.empty()) {
            auto p = pq.top();
            pq.pop();

            int curr = p.second;
            if (rem[curr]) continue;

            best = max<ll>(best, amt * p.first);

            vector<int> children;
            for (int child : g[curr]) children.push_back(child);

            for (int child : children) {
                if (rem[child]) continue;
                g[curr].erase(g[curr].find(child));
                g[child].erase(g[child].find(curr));

                pq.push({g[child].size(), child});
            }

            rem[curr] = true;
            amt--;
        }
         */
    }

    cout << best << endl;
}

void multi_solve() {
    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        solve();
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

    // multi_solve();
    solve();
}



