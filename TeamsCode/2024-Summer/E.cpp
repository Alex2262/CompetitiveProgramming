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
const int CSES_MOD = 1'000'000'000 + 7;


void solve() {
    ll n;
    cin >> n;

    vector<ll> a(n);
    map<ll, int> m;
    ll sum = 0;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        m[a[i]]++;
        sum += a[i];
    }

    vector<ll> bits(32, 0);
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j <= 31; j++) {
            if ((1 << j) & a[i]) bits[j]++;
        }
    }

    sort(a.begin(), a.end());
    ll mx = 0;
    for (ll i = n - 1; i >= 0; i--) {
        ll best = 0;
        m[a[i]]--;
        for (ll j = 31; j >= 0; j--) {
            if (best == 0) {
                if (!(a[i] & (1 << j))) continue;
                bits[j]--;
            }

            if (a[i] & (1 << j)) bits[j]--;

            if (bits[j] < 1) continue;
            // cout << a[i] << " " << j << " " << bits[j] << " " << best << endl;

            if (best == 0) {
                // cout << "WEIRD" << endl;
                best = 1 << j;
                mx = max(mx, best + a[i] - (a[i] ^ best));
                continue;
            }

            if (m[best | (1 << j)] == 0) continue;
            // cout << "HOLA" << endl;
            best |= 1 << j;
        }

        mx = max(mx, best + a[i] - (a[i] ^ best));

        if (best == 0) continue;
    }

    cout << sum - mx << endl;
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