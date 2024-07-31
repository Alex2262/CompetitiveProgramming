
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

using namespace std;
using ll = long long;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

const ll LL_MAX = 9223372036854775807;
const int MAX = 2147483647;
const int MOD = 1'000'000'000 + 7;


void solve() {
    ll n;
    ll x;
    cin >> n >> x;

    vector<ll> w(n);
    for (ll i = 0; i < n; i++) cin >> w[i];

    ll max_bits = (1 << n);
    vector<ll> dp(max_bits, LL_MAX);
    vector<ll> rem(max_bits, LL_MAX);

    dp[0] = 0;
    rem[0] = 0;

    for (ll i = 0; i < max_bits; i++) {
        for (ll j = 0; j < n; j++) {
            if (i & (1 << j)) continue;

            // next subset bit rep
            ll n_s = i | (1 << j);

            ll possible = dp[i] + (w[j] > rem[i]);
            ll new_rem = (w[j] > rem[i]) ? (x - w[j]) : (rem[i] - w[j]);

            if (possible < dp[n_s] || (possible == dp[n_s] && new_rem > rem[n_s])) {
                // cout << possible << " " << new_rem << endl;
                dp[n_s]  = possible;
                rem[n_s] = new_rem;
            }
        }
    }

    cout << dp[max_bits - 1] << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    */
}
