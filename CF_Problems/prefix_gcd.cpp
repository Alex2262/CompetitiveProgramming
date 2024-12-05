#pragma GCC optimize("O3,unroll-loops")
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
 * We should recognize an interesting thing in this problem.
 *
 * Since we want to take numbers that reduce the total number of shared divisors (because of gcd), we
 * can greedily try to find for each i, the element j that minimizes our GCD. But recognize, that we can only have
 * a limited amount of such numbers before it is impossible to reduce the GCD.
 *
 * We call this number max_share, and can say that it is the same as 1 + the smallest
 * number of smallest prime factors that just exceed N.
 *
 * Let's compute this value to be = 8, by 1 + 7. We get our 7 prime factors to be
 * 2 * 3 * 5 * 7 * 11 * 13 * 17 == 510510 which is necessary to exceed 1e5.
 *
 * Why is this so? Let's first recognize that we only need to consider each unique prime factor in our gcd.
 *
 * If we can ultimately remove x instances of prime factor p in our GCD, then it is optimal to simply remove this at
 * the start. Removing x - 1 instances of prime factor p, or x - 2 is always not optimal. So by this, when we
 * look at a unique prime factor, we really only need to consider one number that minimizes the occurences of this
 * prime factor in our GCD.
 *
 * Then, if we are only considering 1 number per unique prime factor, we only need to consider the smallest
 * prime factors in calculating our limit (max_share).
 *
 *
 * By this, we can also recognize that the greedy approach works.
 * We can choose the smallest number to start with, and then optimally remove occurences of prime numbers by
 * whatever reduces the GCD the most.
 *
 */


int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, (a % b));
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int max_share = 7; // we can say that only max_share numbers can share the same divisor

    sort(a.begin(), a.end());

    vector<bool> used(n, false);

    ll ans = a[0];
    used[0] = true;
    int g = a[0];

    for (int i = 1; i < min(n, max_share); i++) {
        int best = a[0];
        int ind = i;

        for (int j = 0; j < n; j++) {
            if (used[j]) continue;

            int tg = gcd(g, a[j]);
            if (tg < best) {
                best = tg;
                ind = j;
            }
        }

        used[ind] = true;
        g = gcd(g, a[ind]);
        ans += g;
    }

    for (int i = min(n, max_share); i < n; i++) {
        g = gcd(g, a[i]);
        ans += g;
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

    // solve();
    multi_solve();
}

