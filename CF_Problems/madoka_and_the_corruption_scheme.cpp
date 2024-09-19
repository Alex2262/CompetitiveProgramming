#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")


/*
 * Problem takeaways:
 *
 * This problem is mainly combinatorics based. But figuring how combinatorics is at play is difficult.
 * We should realize that every parent node will have 2 children with 1 edge used and 1 edge not used.
 *
 * Then, the sponsors can make any number that they want win if it has <= k edges that are not used.
 * We can think about a number having N edges until it wins, so:
 *
 * We can sum up nCi for i <= min(n, k) and this is our answer.
 *
 * This is because the sponsors can make all numbers with i edges s.t. i <= min(n, k) win, so
 * then at minimum, we can only make this number win.
 *
 * For these types of problems, don't think as much about some greedy approach or construction, but rather,
 * how we can transform this problem into something else.
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


ll bin_exp(ll x, ll y) {
    ll res = 1;
    x = x % MOD;
    while (y > 0) {
        if (y & 1) res = (res * x) % MOD;
        y = y >> 1;
        x = (x * x) % MOD;
    }
    return res;
}

ll mod_inverse(ll n) {
    return bin_exp(n, MOD - 2);
}

ll binomial(vector<ll>& fac, vector<ll>& inv, ll n, ll r) {
    if (r == 0) return 1;
    // return (fac[n] * mod_inverse(fac[r]) % MOD * mod_inverse(fac[n - r]) % MOD) % MOD;
    return ((fac[n] * inv[r]) % MOD * inv[n - r]) % MOD;
}

void solve() {
    ll n, k;
    cin >> n >> k;

    vector<ll> fac(n + 1, 1);
    vector<ll> inv(n + 1, 1);
    for (int i = 2; i <= n; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }

    for (int i = 1; i <= n; i++) {
        inv[i] = mod_inverse(fac[i]);
    }

    ll ans = 0;
    for (ll i = 0; i <= min(k, n); i++) {
        ans = (ans + binomial(fac, inv, n, i)) % MOD;
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

    solve();
    // multi_solve();
}

