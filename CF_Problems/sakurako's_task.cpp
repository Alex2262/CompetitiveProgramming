#pragma GCC optimize("O3,unroll-loops")
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

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, (a % b));
}

void solve() {
    ll n, k;
    cin >> n >> k;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    ll g = a[0];

    for (int i = 0; i < n; i++) {
        g = gcd(g, a[i]);
    }

    if (n > 1) {
        for (int i = 0; i < n; i++) {
            a[i] = i * g;
        }
    }

    ll prev = -1;
    ll ans = -1;

    for (int i = 0; i < n; i++) {
        ll diff = a[i] - prev - 1;

        if (diff >= k) {
            ans = prev + k;
            k = 0;
            break;
        }

        k -= diff;
        prev = a[i];

        ans = a[i];
    }

    ans += k;

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

