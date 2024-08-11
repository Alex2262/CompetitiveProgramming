
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

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, (a % b));
}


#define lsb         __builtin_ctz
#define msb         __builtin_clz


void solve() {
    ll n, k;
    cin >> n >> k;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    if (equal(a.begin() + 1, a.end(), a.begin())) {
        cout << 0 << endl;
        return;
    }

    ll mn = *min_element(a.begin(), a.end());
    ll mx = *max_element(a.begin(), a.end());

    if (k >= mn && k <= mx) {
        cout << -1 << endl;
        return;
    }

    vector<ll> b(n);
    for (int i = 0; i < n; i++) {
        b[i] = abs(a[i] - k);
    }

    ll g = b[0];
    for (int i = 1; i < n; i++) g = gcd(g, b[i]);

    ll best_ops = LL_MAX;

    ll t;
    if (k < mn) t = k + g;
    else t = k - g;

    // cout << "T " << t << endl;

    ll ops = 0;
    for (int i = 0; i < n; i++) {
        ops += abs(a[i] - t) / abs(t - k);
    }

    // cout << "OPS " << ops << endl;

    best_ops = min(best_ops, ops);

    if (best_ops == LL_MAX) cout << -1 << endl;
    else cout << best_ops << endl;



    // make everything mn.
    // a_i + x * (k - mn) == mn
    // x * (k - mn) == mn - a_i
    // x == (mn - a_i) / (k - mn)
    // x == (40 - 100) / (10 - 40)
    // x == (a_i - mn) / (mn - k)

    // x == (t - a_i) / (k - t)
    // x == (a_i - t) / (t - k)
    // x == -1 * (a_i - t) / (k - t)

    // (a_i - t) % (t - k) == 0
    // let y = t - k
    // t = y + k

    // (a_i - (y + k)) % y == 0
    // (a_i - k - y) % y == 0

    // a_i - k - y == m * y
    // m * y + y == a_i - k
    // y * (m + 1) == a_i - k
    // y == (a_i - k) / (m + 1)

    // t = y + k



    // either: k < t <= a_i  or a_i <= t < k
    // so k has to be < mn or > mx.

    // we can start by trying to maximize abs(t - k) to get the least num of operations
    // so we know:
    // if k > mx we can search the window of t in [mn, k)
    // if k < mn we can search the window of t in (k, mx]

    // (a_i - t) % (t - k) == 0
    // a_i - t = m * (t - k)
    // a_i - t = m * t - m * k
    // m * t + t = m * k - a_i
    // t * (m + 1) = m * k - a_i
    // t = (m * k - a_i) / (m + 1)





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

    // /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    // */
}

