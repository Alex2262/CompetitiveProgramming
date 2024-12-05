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
// const ll MOD = 1'000'000'000 + 7;
const ll MOD2 = 998'244'353;


/*
 *
 *
 *
 */


vector<int> topological_sort(vector<vector<int>>& g) {

    int n = g.size();

    vector<int> in_degree(n, 0);

    for (int i = 0; i < n; i++) {
        for (int child : g[i]) {
            in_degree[child]++;
        }
    }


    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    int visited = 0;
    vector<int> sorted;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        sorted.push_back(node);

        for (int child : g[node]) {
            in_degree[child]--;
            if (in_degree[child] == 0) {
                q.push(child);
            }
        }

        visited++;
    }

    return sorted;
}

void add(ll& entry, ll amt) {
    entry = (entry + amt) % MOD2;
}

void sub(ll& entry, ll amt) {
    entry = (entry - amt + MOD2) % MOD2;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<vector<int>> g(n);
    vector<vector<int>> bg(n);
    vector<int> in_degree(n, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        g[u].push_back(v);
        bg[v].push_back(u);

        in_degree[v]++;
    }

    vector<int> order = topological_sort(g);


    vector<ll> times(n, 0);

    ll ans = 0;

    for (int node : order) {
        times[node] = a[node];

        if (in_degree[node] > 0) {
            times[node] = max<ll>(times[node], 1);
        }

        ll curr = 0;

        for (int parent : bg[node]) {
            add(times[node], times[parent]);
            curr = max(curr, times[parent]);
        }

        cout << node + 1 << " " << times[node] << endl;
    }

    for (int i = 0; i < n; i++) ans = max(ans, times[i]);

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

    multi_solve();
}


