
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
const int MOD = 1'000'000'000 + 7;
// const int MOD2 = 998'244'353;


ll bin_exp(ll x, ll y) {
    ll res = 1;
    x = x % MOD;
    while (y > 0) {
        if (y & 1)
            res = (res * x) % MOD;
        y = y >> 1;
        x = (x * x) % MOD;
    }
    return res;
}

long long mod_inverse(long long n) {
    return bin_exp(n, MOD - 2);
}

// nCr
ll binomial(vector<ll>& fac, ll n, ll r) {
    if (r == 0) return 1;
    return (fac[n] * mod_inverse(fac[r]) % MOD * mod_inverse(fac[n - r]) % MOD) % MOD;
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<ll> fac(n + 1);
    fac[0] = 1;
    fac[1] = 1;
    for (ll i = 2; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;

    int c0 = 0, c1 = 0;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;

        if (t == 0) c0++;
        else c1++;
    }

    if (c1 < k / 2 + 1) {
        cout << 0 << endl;
        return;
    }

    ll ans = 0;

    // cout << c1 << " " << c0 << endl;

    for (int i = k / 2 + 1; i <= k; i++) {
        if (i > c1) break;
        ll right = (k - i) > c0 ? 0 : binomial(fac, c0, k - i);

        // cout << i << " " << binomial(fac, c1, i) << " " << right << endl;
        ans = (ans + (binomial(fac, c1, i) * right) % MOD) % MOD;
    }

    cout << ans << endl;
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

    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}

