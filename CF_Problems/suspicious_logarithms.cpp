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


#define popcount    __builtin_popcount


struct Range {
    ll l, r;
    int bit;
};

void solve() {
    ll l, r;
    cin >> l >> r;


    vector<Range> ranges;
    for (int i = 0; i <= 60; i++) {
        ll b = (1LL << i);

        if (b <= l) continue;

        ll prev = (1LL << (i - 1));
        ranges.push_back({max(prev, l), min(b - 1, r), i - 1});

        if (b > r) break;
    }

    int m = ranges.size();
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        // cout << "CURR " << ranges[i].l << " " << ranges[i].r << " " << ranges[i].bit << endl;

        ll g = ranges[i].bit;

        ll ops = 1;
        while (g <= ranges[i].l / ranges[i].bit) {
            g *= ranges[i].bit;
            ops++;
        }

        // cout << "INIT " << g << " " << ops << endl;

        while (g <= ranges[i].r / ranges[i].bit) {
            ll next = g * ranges[i].bit;
            ll len = min(next - 1LL, ranges[i].r) - max(g, ranges[i].l) + 1LL;

            // cout << g << " " << len << endl;

            ans = (ans + (len * ops) % MOD) % MOD;

            g = next;
            ops++;
        }

        ll next = ranges[i].r;
        ll len = next - max(g, ranges[i].l) + 1LL;

        // cout << g << " " << len << endl;

        ans = (ans + (len * ops) % MOD) % MOD;
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

    // ios_base::sync_with_stdio(false);
    // cin.tie(nullptr);

    // solve();
    multi_solve();
}




