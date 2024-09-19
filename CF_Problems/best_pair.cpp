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

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    set<pii> bad;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        bad.insert({u, v});
    }

    map<ll, ll> ma;
    for (int i = 0; i < n; i++) ma[a[i]]++;

    vector<pll> b;
    for (auto e : ma) {
        b.emplace_back(e.first, e.second);
    }

    n = b.size();

    sort(b.begin(), b.end(), greater<>());

    map<ll, vector<ll>> occ;
    for (int i = 0; i < n; i++) {
        occ[b[i].second].push_back(b[i].first);
    }

    ll ans = 0;

    // cout << n << endl;

    for (int i = 0; i < n; i++) {

        ll x = b[i].first;
        ll cnt = b[i].second;

        // cout << x << " " << cnt << endl;

        for (int j = cnt; j >= 1; j--) {
            for (auto y : occ[j]) {
                if (x == y) continue;
                if (bad.find({x, y}) != bad.end()) continue;
                if (bad.find({y, x}) != bad.end()) continue;

                ans = max(ans, (cnt + j) * (x + y));

                // cout << "MAXXING " << j << " " << y << " " << (cnt + j) * (x + y) << endl;
                break;
            }
        }
    }

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

