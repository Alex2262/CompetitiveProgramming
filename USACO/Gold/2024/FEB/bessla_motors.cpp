#pragma GCC optimize("O2,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

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
// const ll MOD = 1'000'000'000 + 7;
// const ll MOD = 998'244'353;

const ll MOD = 3359232;


/*
 * Problem takeaways:
 *
 * Very interesting idea that you can run dijkstra's kind of in parallel by starting from multiple sources.
 *
 * Another interesting idea is that we just don't need to store the distance in order for dijkstra's to work,
 * since it seems that the priority queue will completely handle it. We just need to store visits it looks like.
 *
 * This should be true because dijkstra's algorithm will only ever visit each node once
 * (visit meaning that we check a node's children etc and process it). Once the node is popped from the priority
 * queue, it has to be the optimal distance to the node. We can intuit why this is true.
 *
 * Imagine there are multiple ways to reach a node, then in the priority queue, we will take the least of these
 * distances. Then, you might imagine, what if we didn't uncover a potential path that can reach a node yet?
 *
 * This is not an issue, because if that path is a shorter distance than any distance to the node currently,
 * we will look at it first. However, if that potential path is a longer distance, it will go behind in
 * the priority queue, as it can never be a shorter distance to a node.
 *
 *
 */


void solve() {
    int n, m, c, r, k;
    cin >> n >> m >> c >> r >> k;

    vector<vector<pll>> g(n);
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;

        u--, v--;

        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<>> pq;

    vector<set<int>> vis(n);
    vector<int> cnt(n, 0);

    for (int i = 0; i < c; i++) {
        pq.push({0, i, i});
    }

    while (!pq.empty()) {
        auto p = pq.top();
        pq.pop();

        ll dist = p[0];
        ll node = p[1];
        ll src = p[2];

        if (cnt[node] >= k) continue;
        if (vis[node].find(src) != vis[node].end()) continue;

        // cout << "VISITING " << dist << " " << node << " " << src << endl;

        vis[node].insert(src);
        cnt[node]++;

        for (auto pc : g[node]) {
            ll child = pc.first;
            ll weight = pc.second;

            ll new_dist = dist + weight;

            if (new_dist > r) continue;

            if (cnt[child] < k && vis[child].find(src) == vis[child].end()) {
                // cout << "GOING FROM " << node << " " << child << endl;
                pq.push({new_dist, child, src});
            }
        }
    }

    vector<int> ans;

    for (int i = c; i < n; i++) {
        // cout << i << " " << cnt[i] << endl;
        if (cnt[i] >= k) {
            ans.push_back(i);
        }
    }

    cout << ans.size() << endl;
    for (auto e : ans) {
        cout << e + 1 << endl;
    }
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

    // solve();
    solve();
}



