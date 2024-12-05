#pragma GCC optimize("O2,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

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
// const ll MOD = 1'000'000'000 + 7;
const ll MOD = 998'244'353;



/*
 * Cool problem idea:
 *
 * We can fix the number of attacks we have (through binary search on the min),
 *
 * then, with a fixed number of attacks, we get a new amount of health for each monster by doing
 * ceil(health / (# of attacks))
 *
 * and then, we interpret it as each monster having a window where p needs to be in for the monster to die.
 * So now, we can consider each one as an event, and then find the maximum number of events occuring at a time
 *
 *
 */


void solve() {
    int n;
    ll m, k;
    cin >> n >> m >> k;

    vector<ll> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    vector<ll> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];

    ll l = 1, r = 1e16;

    ll ans = -1;

    while (l <= r) {
        ll mid = l + (r - l) / 2;

        vector<pll> amts;

        for (int i = 0; i < n; i++) {
            ll base = (h[i] + mid - 1) / mid;

            if (base > m) continue;
            ll need = m - base;

            ll low = x[i] - need;
            ll high = x[i] + need;

            amts.push_back({low, 1});
            amts.push_back({high + 1, -1});
        }

        sort(amts.begin(), amts.end());

        int best = 0;
        int curr = 0;

        int j = 0;

        for (int i = 0; i < amts.size(); i++) {
            curr += amts[i].second;
            best = max(best, curr);
        }

        if (best >= k) {
            r = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }

    if (ans == -1) {
        cout << -1 << endl;
        return;
    }

    cout << ans << endl;
}


void multi_solve() {
    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        solve();
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

    // solve();
    multi_solve();
    // stress();
}



