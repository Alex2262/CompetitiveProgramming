// #include <cstdio>

/*
 * Problem takeaways:
 *
 * This is some greedy/bruteforce implementation problem.
 * The key here is really to notice that we always need to place our blocks of length 2 first, since otherwise
 * our 1s can just go around them.
 *
 * For the case of minimum, we find all adjacent 1s and we use our 2s here, and the rest of the 1s we can simply
 * add up.
 *
 * For the case of maximum, we notice that we just never want to put our 2s where there are adjacent 1s.
 * So we deal with this first, then place down all remaining 2s in places that we can and add score correspondingly.
 * The rest of the lights that are on, we can add to our score.
 *
 * If this comes up in a competition, it is important to think about the best way to implement the solution,
 * and what we *must* do in order to avoid edgecases. The key idea here is to ensure we always place our 2s first.
 *
 * It is easy to assume we can just loop through greedily, but we must take some extra care to ensure our
 * 2s are always placed optimally first.
 */

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
    int n, m;
    cin >> n >> m;

    vector<vector<bool>> on(n, vector<bool>(m));

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        for (int j = 0; j < m; j++) on[i][j] = (s[j] == '1');
    }

    ll mn = 0, mx = 0;
    for (int i = 0; i < n; i++) {
        ll c2 = 0;
        int j = 0;
        for (; j < m - 1; j++) {
            if (on[i][j] && on[i][j + 1] && c2 != m / 4) {
                c2++;
                mn++;
                j++;
                continue;
            }

            mn += on[i][j];
        }

        if (j == m - 1) mn += on[i][j];

        c2 = 0;
        ll num = 0;
        vector<bool> used(m, false);
        for (j = 0; j < m - 1 && c2 != m / 4; j++) {
            if (on[i][j] && on[i][j + 1]) continue;

            mx += on[i][j] | on[i][j + 1];
            used[j] = true;
            used[j + 1] = true;
            c2++;
            j++;
        }

        for (j = 0; j < m; j++) {
            if (used[j]) continue;
            if (j < m - 1 && !used[j + 1] && c2 != m / 4) {
                mx += on[i][j] | on[i][j + 1];
                j++;
                c2++;
                continue;
            }

            num += on[i][j];
        }

        mx += num;

    }

    cout << mn << " " << mx << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
     */
}