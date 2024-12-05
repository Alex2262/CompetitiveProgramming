#pragma GCC optimize("O3,unroll-loops")
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


void dijkstra(vector<vector<pll>>& g, vector<vector<ll>>& dists, vector<bool>& horse, int n, int start) {

    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<>> pq;
    pq.push({0, start, horse[start]});

    for (int i = 0; i < n; i++) {
        dists[i][0] = 1e16;
        dists[i][1] = 1e16;
    }

    dists[start][0] = 0;

    if (horse[start]) dists[start][1] = 0;

    while (!pq.empty()) {
        auto p = pq.top();
        pq.pop();

        ll dist = p[0];
        ll node = p[1];
        bool has = p[2];

        if (dist > dists[node][has]) continue;

        bool next_has = has | horse[node];

        // cout << dist << " " << node << " " << has << endl;

        for (auto pc : g[node]) {
            ll child = pc.first;
            ll weight = pc.second;

            if (next_has) weight /= 2;

            ll new_dist = dists[node][has] + weight;

            if (new_dist < dists[child][next_has]) {
                dists[child][next_has] = new_dist;
                pq.push({dists[child][next_has], child, next_has});
            }
        }
    }
}


void solve() {
    int n, m, h;
    cin >> n >> m >> h;

    vector<bool> horse(n, false);
    for (int i = 0; i < h; i++) {
        int x;
        cin >> x;
        x--;

        horse[x] = true;
    }

    vector<vector<pll>> g(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    vector<vector<ll>> dists1(n, vector<ll>(2));
    vector<vector<ll>> dists2(n, vector<ll>(2));

    dijkstra(g, dists1, horse, n, 0);
    dijkstra(g, dists2, horse, n, n - 1);

    ll ans = 1e16;

    for (int i = 0; i < n; i++) {
        // cout << i << " " << min(dists1[i][0], dists1[i][1]) << " " << min(dists2[i][0], dists2[i][1]) << endl;
        ans = min(ans, max(min(dists1[i][0], dists1[i][1]), min(dists2[i][0], dists2[i][1])));
    }

    // ll ans = min(min(dists1[n - 1][0], dists1[n - 1][1]), min(dists2[0][0], dists2[0][1]));

    if (ans == 1e16) ans = -1;
    cout << ans << endl;

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

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // solve();
    multi_solve();
}

