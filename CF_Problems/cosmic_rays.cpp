// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

/*
 * idea for the problem isn't very hard to come up with,
 * but we need to just think of this simple implementation for the problem with stacks instead of thinking
 * about segtree or PQ or any more complex DS.
 *
 *
 *
 */


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
 *
 *
 *
 *
 *
 */


void solve() {
    int n;
    cin >> n;

    vector<ll> a(n);
    vector<int> b(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cin >> b[i];
    }

    stack<pll> s;
    ll curr = 0;



    for (int i = 0; i < n; i++) {
        ll inter = 0;

        while (!s.empty()) {
            auto p = s.top();
            // cout << i << " " << p.first << " " << p.second << endl;

            if (p.second == b[i]) {
                a[i] += p.first - inter;
                s.pop();
                continue;
            }

            if (p.first >= a[i]) break;

            s.pop();
            inter = max(inter, p.first);
        }

        s.emplace(a[i], b[i]);
        curr = max(curr, a[i]);
        cout << curr;

        if (i != n - 1) cout << " ";
    }

    cout << endl;
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

