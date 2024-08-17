
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")


/*
 * Problem takeaways:
 *
 * We should realize that this is kind of like dijkstra's except we can simply consider all edges,
 * and when we want to travel to the next child node, we simply want to take the next node that has the least
 * time that is greater than ours. We can do this by binary searching, and ultimately our largest time is our
 * answer.
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
    int n, t;
    cin >> n >> t;

    vector<vector<pll>> g(n);

    for (int i = 0; i < t; i++) {
        int m;
        cin >> m;

        for (int j = 0; j < m; j++) {
            int a, b;
            cin >> a >> b;
            a--, b--;

            g[a].push_back({b, i});
            g[b].push_back({a, i});
        }
    }

    int k;
    cin >> k;

    vector<set<int>> times(t);
    for (int i = 0; i < k; i++) {
        int a;
        cin >> a;
        a--;

        times[a].insert(i + 1);
    }

    priority_queue<pll, vector<pll>, greater<>> pq;

    vector<int> best(n, MAX);

    pq.push({0, 0});
    best[0] = 0;

    while (!pq.empty()) {
        auto p = pq.top();
        pq.pop();

        ll curr_dist = p.first;
        ll node = p.second;

        // not optimal anymore
        if (curr_dist > best[node]) continue;

        for (auto pc : g[node]) {
            int child = pc.first;
            int child_time = pc.second;

            // If there is a way to reach the child node
            auto next = times[child_time].upper_bound(best[node]);
            if (next == times[child_time].end()) continue;

            if (*next < best[child]) {
                best[child] = *next;
                pq.emplace(best[child], child);
            }
        }
    }

    if (best[n - 1] == MAX) cout << -1 << endl;
    else cout << best[n - 1] << endl;
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

