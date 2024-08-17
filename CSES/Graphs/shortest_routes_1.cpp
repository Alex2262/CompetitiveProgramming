
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

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<pll>> g(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        a--, b--;

        g[a].push_back({b, c});
    }

    priority_queue<pll, vector<pll>, greater<>> pq;

    pq.push({0, 0});

    ll dists[n];
    for (int i = 0; i < n; i++) dists[i] = 1e16;
    dists[0] = 0;

    while (!pq.empty()) {
        auto p = pq.top();
        pq.pop();

        ll dist = p.first;
        ll node = p.second;

        if (dist > dists[node]) continue; // no longer optimal

        for (auto pc : g[node]) {
            ll child = pc.first;
            ll weight = pc.second;

            ll new_dist = dists[node] + weight;
            if (new_dist < dists[child]) {
                dists[child] = new_dist;
                pq.push({dists[child], child});
            }
        }
    }

    string s;
    for (int i = 0; i < n; i++) {
        s += to_string(dists[i]);
        if (i != n - 1) s += " ";
    }

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

