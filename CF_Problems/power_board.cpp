#pragma GCC optimize("O3,unroll-loops")
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
// const ll MOD2 = 998'244'353;


/*
 * Problem takeaways:
 *
 * First, let's notice that each number can be expressed by its prime factorization.
 *
 * Such as 12 = 2 ^ 2 * 3 ^ 1, and we can take the GCD of the powers of each unique prime factor, and then
 * we can achieve tha base of this number. For example, 8 = 2^3 where its base is 2.
 *
 * Then, let's notice that two i values can only ever have coinciding powers if their bases are the same.
 *
 * For example:
 * take rows 2 and 4
 *
 * 2^1, 2^2, 2^3, 2^4
 * 4^1, 4^2, 4^3, 4^4
 *
 * we can express them as
 *
 * 2^1, 2^2, 2^3, 2^4
 * 2^(2*1), 2^(2*2), 2^(2*3), 2^(2*4)
 *
 * then we have:
 *
 * 2^1, 2^2, 2^3, 2^4
 * 2^2, 2^4, 2^6, 2^8
 *
 * so we are able to achieve this in log n for each i, by sieving for prime factors at the start.
 * But how do we figure out overlaps?
 *
 * Our final observation that is very important is that:
 * 1. For each base, we can have at most 20 powers (since 2^20 > 1e6 right, notice that this 20 is log_2(n))
 * 2. For each base, we can do brute force computation on the powers to figure out how many unique counts
 * we can achieve for each row like so:
 *
 * for base 2, let's look at only the powers:
 *
 * 1, 2, 3, 4
 * 2, 4, 6, 8
 *
 * then we will brute force in O(20 * m) to figure out how many new values each row adds, but this would still
 * be too slow to compute for every base.
 *
 * But, we realize that these row computations will be the exact same for any base.
 * For example, for base 3, if we have two rows, we will still have:
 *
 * 1, 2, 3, 4
 * 2, 4, 6, 8
 *
 * So we just compute the number of unique numbers added at the start for each row number, and this
 * can be used for all bases.
 *
 * Our final time complexity is O(n log n + n log log n + n log n)
 *
 * so O(n log n)
 *
 *
 *
 */


const int N = 1e6 + 5;


vector<int> sieve_factors(int n) {
    vector<int> prime_factor;
    prime_factor.resize(n + 1);

    prime_factor[0] = 1;  // we should not use this...
    prime_factor[1] = 1;

    for (int i = 2; i < n; i++) {
        if (i & 1) prime_factor[i] = i;
        else prime_factor[i] = 2;
    }

    for (int p = 3; p * p <= n; p++) {
        if (prime_factor[p] != p) continue;

        for (int i = p * p; i <= n; i += p) prime_factor[i] = p;
    }

    return prime_factor;
}

void prime_factors_sieve(vector<int>& prime_factor, map<int, int>& m, int n) {
    if (n <= 1) return;

    while (n > 1) {
        m[prime_factor[n]]++;
        n /= prime_factor[n];
    }
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, (a % b));
}

ll bin_exp(ll x, ll y) {
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
    ll n, m;
    cin >> n >> m;

    vector<bool> used(20 * (m + 1) + 1, false);
    vector<int> dp(21, 0);

    for (int i = 1; i <= 20; i++) {
        int ans = 0;
        for (int j = 1; j <= m; j++) {
            if (!used[i * j]) {
                used[i * j] = true;
                ans++;
            }
        }

        dp[i] = ans;
    }

    vector<int> prime_factor = sieve_factors(N);

    ll ans = 1;

    for (ll i = 2; i <= n; i++) {
        map<int, int> ma;
        prime_factors_sieve(prime_factor, ma, i);

        vector<int> pows;
        for (auto p : ma) {
            pows.push_back(p.second);
        }

        ll g = pows[0];
        for (int j = 1; j < pows.size(); j++) {
            g = gcd(g, pows[j]);
        }

        ll b = 1;
        for (auto p : ma) {
            b *= bin_exp(p.first, p.second / g);
        }

        ans += dp[g];
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

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}


