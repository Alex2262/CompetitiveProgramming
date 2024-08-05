// #include <cstdio>

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

#define popcount    __builtin_popcount
#define popcount_ll __builtin_popcountll
#define lsb         __builtin_ctz
#define lsb_ll      __builtin_ctzll
#define msb         __builtin_clz
#define msb_ll      __builtin_clzll
#define parity      __builtin_parity

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

const ll LL_MAX = 9223372036854775807;
const int MAX = 2147483647;
// const int MOD = 1'000'000'000 + 7;
const int MOD2 = 998'244'353;

void solve() {
    int n;
    cin >> n;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        b[i]--;
    }

    vector<bool> used(n);
    vector<int> order;

    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) {
        if (b[i] == -2) continue;
        g[i].push_back(b[i]);
    }

    ll ans = 0;

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
        if (a[node] >= 0) {
            ans += a[node];
            order.push_back(node + 1);
            used[node] = true;
            if (b[node] != -2) {
                a[b[node]] += a[node];
            }
        }

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

    for (int i = sorted.size() - 1; i >= 0; i--) {
        int node = sorted[i];
        if (used[node]) continue;
        used[node] = true;

        ans += a[node];
        order.push_back(node + 1);

        if (b[node] != -2) a[b[node]] += a[node];
    }

    cout << ans << endl;

    string s = to_string(order[0]);
    for (int i = 1; i < n; i++) s += " " + to_string(order[i]);

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

