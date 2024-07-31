// #include <cstdio>

#include <deque>
#include <iostream>
#include <vector>
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


ll binpow(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

ll modinverse(ll a) {
    return binpow(a, MOD - 2);
}

void solve() {
    int n;
    cin >> n;

    if (n == 1) {
        cout << 1 << endl;
        return;
    }

    if (n == 3) {
        cout << (7 * modinverse(6) % MOD) << endl;
        return;
    }

    vector<ll> dp_num(n);
    vector<ll> dp_den(n);
    dp_num[0] = 1;
    dp_den[0] = 1;

    for (int i = 1; i < n - 1; i++) {
        dp_num[i] = ((dp_num[i - 1] * (i + 1) % MOD) + (((1 + dp_num[i - 1]) % MOD) * (i)) % MOD) % MOD;
        dp_den[i] = (dp_den[i - 1] * (i + 1)) % MOD;
    }

    // dp_num[n - 1] =

    // cout << dp_num[n - 1] / dp_den[n - 1] << endl;
    // cout << dp_num[n - 2] << " " << dp_den[n - 2] << endl;
    // cout << (28 * modinverse(30) % MOD) << endl;
    cout << (dp_num[n - 2] * modinverse(dp_den[n - 2])) % MOD << endl;


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