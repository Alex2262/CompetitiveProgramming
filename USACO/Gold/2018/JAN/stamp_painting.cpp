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
const ll MOD = 1'000'000'000 + 7;
// const ll MOD = 998'244'353;


/*
 * Problem Observations:
 *
 *
 * For this problem, we should realize that we just need to figure out all the number of ways we can stamp
 * such that at the end, we have k colors in a row. Every combination with at least k colors in a row will
 * satisfy our needs.
 *
 *
 */


void add(ll& entry, ll amt) {
    entry = (entry + amt) % MOD;
}

void sub(ll& entry, ll amt) {
    entry = (entry - amt + MOD) % MOD;
}

ll binpow(ll x, ll y) {
    x %= MOD;

    ll res = 1;
    while (y > 0) {
        if (y & 1) res = (res * x) % MOD;
        x = (x * x) % MOD;
        y = y >> 1;
    }

    return res;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;


    if (k == 1) {
        ll ans = binpow(m, n);
        cout << ans << endl;
        return;
    }

    /*
    ll dp[k];

    for (int i = 0; i < k; i++) {
        dp[i] = 0;
    }

    dp[0] = m;
     */

    ll dp_last = 0;
    ll s = 0;

    deque<ll> dq;
    dq.push_back(m);
    for (int j = 1; j < k - 1; j++) dq.push_back(0);
    s = m;

    for (int i = 1; i < n; i++) {

        ll ndp0 = ((m - 1) * s) % MOD;
        ll ndp_last = (m * dp_last) % MOD;

        ndp_last = (ndp_last + dq.back()) % MOD;

        add(s, ndp0);

        sub(s, dq.back());

        dq.pop_back();
        dq.push_front(ndp0);

        dp_last = ndp_last;

        /*
        // O(NK) DP
        ll ndp[k];
        for (int j = 0; j < k; j++) ndp[j] = 0;

        for (int j = 0; j < k; j++) {
            if (dp[j] == 0) continue;

            if (j == k - 1) {
                add(ndp[j], (m * dp[j]) % MOD);
            }

            else {
                add(ndp[j + 1], dp[j]);
                add(ndp[0], ((m - 1) * dp[j]) % MOD);
            }
        }

        for (int j = 0; j < k; j++) dp[j] = ndp[j];
        */
    }

    // cout << dp[k - 1] << endl;
    cout << dp_last << endl;
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

    // freopen("spainting.in", "r", stdin);
    // freopen("spainting.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}


