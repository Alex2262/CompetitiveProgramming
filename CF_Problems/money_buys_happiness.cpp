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
const int CSES_MOD = 1'000'000'000 + 7;

void solve() {
    ll m, x;
    cin >> m >> x;

    vector<ll> cost(m);
    vector<ll> h(m);

    ll h_sum = 0;
    for (int i = 0; i < m; i++) {
        cin >> cost[i];
        cin >> h[i];

        h_sum += h[i];
    }

    if (cost[0] != 0) {
        h_sum -= h[0];
        cost[0] = LL_MAX;
    }

    vector<ll> dp(h_sum + 1, -1);
    dp[0] = 0;

    ll max_cost = (m - 1) * x;

    for (ll i = 0; i < m; i++) {
        for (ll j = h_sum; j >= 0; j--) {
            if (dp[j] == -1) continue;
            if (dp[j] + cost[i] > i * x) continue;

            if (dp[j + h[i]] == -1) dp[j + h[i]] = dp[j] + cost[i];
            else dp[j + h[i]] = min(dp[j + h[i]], dp[j] + cost[i]);

            // cout << j + h[i] << " " << dp[j] << " " << cost[i] << endl;
        }
    }

    ll best = 0;
    for (ll j = h_sum; j >= 0; j--) {
        if (dp[j] != -1 && dp[j] <= max_cost) {
            best = j;
            break;
        }
    }

    // cout << "LMAOOOOO " << m << " " << x << endl;
    cout << best << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //solve();

    // /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    // */
}