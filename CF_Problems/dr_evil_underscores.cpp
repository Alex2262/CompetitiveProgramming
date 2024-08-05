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

    set<ll> s;
    for (int i = 0; i < n; i++) {
        ll t;
        cin >> t;
        s.insert(t);
    }

    vector<ll> a;
    for (ll e : s) a.push_back(e);

    n = a.size();

    ll l = 0, r = *max_element(a.begin(), a.end());
    while (l < r) {
        ll target = l + (r - l) / 2;
        bool works = true;



        if (works) {
            r = target;
        } else l = target + 1;
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


    solve();

    /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    */
}

