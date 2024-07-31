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
const int MOD = 1'000'000'000 + 7;
// const int MOD2 = 998'244'353;

ll dfs(vector<vector<int>>& g, vector<ll>& a, int node, int parent) {


    ll mn = LL_MAX;
    for (int child : g[node]) {
        if (child == parent) continue;
        mn = min(mn, dfs(g, a, child, node));
    }

    if (mn == LL_MAX) return a[node];

    if (node == 0) {
        a[node] += mn;
        return 0;
    }

    if (mn <= a[node]) return mn;

    ll sum = a[node] + mn;
    ll avg = ceil(sum / 2.0);
    mn = sum - avg;

    a[node] = avg;

    return min(a[node], mn);
}


void solve() {
    int n;
    cin >> n;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<vector<int>> g(n);

    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;

        g[p].push_back(i);
    }

    dfs(g, a, 0, -1);

    cout << a[0] << endl;


}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // solve();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}
