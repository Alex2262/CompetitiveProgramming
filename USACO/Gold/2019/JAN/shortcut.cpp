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
const ll MOD2 = 998'244'353;


/*
 *
 *
 *
 */



class Compare {
public:
    bool operator() (array<ll, 3> a, array<ll, 3> b) {
        if (a[0] < b[0]) return true;
        if (a[0] > b[0]) return false;

        if (a[2] < b[2]) return false;
        if (a[2] > b[2]) return true;

        return true;
    }
};

void solve() {
    int n, m, t;
    cin >> n >> m >> t;

    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];

    vector<vector<pll>> g(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--, v--;

        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<>> pq;

    int src = 0;

    vector<array<ll, 2>> dists(n, array<ll, 2> {LL_MAX, LL_MAX});



    pq.push({0, src, -1});
    dists[src] = {0, -1};

    while (!pq.empty()) {
        auto p = pq.top();
        pq.pop();

        ll dist = p[0];
        ll node = p[1];
        ll prev = p[2];

        // cout << "CONSIDERING " << node + 1 << " prev " << prev + 1 << endl;

        if (dist > dists[node][0]) continue; // no longer optimal
        if (prev > dists[node][1]) continue;

        // cout << "VISITING " << node + 1 << " prev " << prev + 1 << endl;

        dists[node][1] = min<ll>(dists[node][1], prev);

        for (auto pc : g[node]) {
            ll child = pc.first;
            ll weight = pc.second;


            // cout << "TESTING " << node + 1 << " " << child + 1 << endl;

            if (dists[node][0] == LL_MAX) continue;
            ll new_dist = dists[node][0] + weight;

            if (new_dist < dists[child][0] || (new_dist == dists[child][0] && node < dists[child][1])) {
                // cout << "ADDED " << node + 1 << " " << child + 1 << endl;
                // cumdist[child] -= c[child] * dists[child][0];

                dists[child][0] = new_dist;
                dists[child][1] = node;

                // cumdist[child] += c[child] * new_dist;

                pq.push({dists[child][0], child, node});
            }
        }
    }

    vector<ll> tot(n, 0);

    for (int i = 1; i < n; i++) {
        int j = i;
        tot[i] += c[i];
        // cout << i + 1 << " " << dists[i][0] << " " << dists[i][1] + 1 << endl;

        while (j != 0) {
            j = dists[j][1];
            tot[j] += c[i];
        }
    }

    ll best = 0;
    for (int i = 1; i < n; i++) {
        best = max(best, tot[i] * (dists[i][0] - t));
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

    freopen("shortcut.in", "r", stdin);
    freopen("shortcut.out", "w", stdout);

    /*
     * FAST IO
     * Remember to remove for interactive problems!!!
     * https://stackoverflow.com/questions/31162367/significance-of-ios-basesync-with-stdiofalse-cin-tienull
     */

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}


