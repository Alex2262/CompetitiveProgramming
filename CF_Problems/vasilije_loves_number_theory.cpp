
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
// const int MOD = 1'000'000'000 + 7;
const int MOD2 = 998'244'353;

/*
 *
 *
 *
 */


void prime_factors(map<ll, ll>& m, ll n) {
    while (n % 2 == 0) {
        m[2]++;
        n = n / 2;
    }

    for (int i = 3; i <= sqrt(n); i = i + 2) {
        while (n % i == 0) {
            m[i]++;
            n = n / i;
        }
    }

    if (n > 2) m[n]++;
}

void solve() {
    int n, q;
    cin >> n >> q;

    map<ll, ll> m_orig;

    prime_factors(m_orig, n);

    map<ll, ll> m = m_orig;

    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;

        if (k == 2) {
            m = m_orig;
            continue;
        }

        ll x;
        cin >> x;

        prime_factors(m, x);

        ll d = 1;
        for (auto e : m) {
            // cout << e.first << " " << e.second << endl;
            d *= (e.second + 1);
        }

        map<ll, ll> test;
        prime_factors(test, d);

        // cout << d << endl;

        bool works = true;
        for (auto e : test) {
            if (m[e.first] < e.second) {
                works = false;
                break;
            }
        }

        if (works) cout << "YES";
        else cout << "NO";
        cout << endl;
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

    // /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    // */
}

