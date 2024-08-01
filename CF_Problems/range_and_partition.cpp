// #include <cstdio>

/*
 * Problem takeaways:
 *
 * This is quite a difficult greedy problem. We first should think about the approach to test the range of numbers
 * [x, y]. How do we do this? Well we can greedily loop through the array, and if we have a elements within the
 * range, and b elements outside, then once a == b + 1, we know it is optimal to greedily cut (unless it's the last
 * segment).
 *
 * Then, we realize if we have k such subsets, our total frequency >= ceil((n + k) / 2).
 *
 * But this is still difficult. How would we find [x, y] right now?
 *
 * Well we more observation is necessary. If we have a valid [x, y], it doesn't matter where these numbers appear.
 * Since they satisfy our equation, we can always make a segment as short or as long as required, and we will
 * achieve the answer.
 *
 * For example, if all our elements [x, y] are at the end of the array, our first segment
 * will be long enough such that a == b + 1, then we'll take sizes of 1 next to get our answer.
 *
 * But what if they are at the front of the array? Well then we will take sizes of 1 (remember 1 == 0 + 1, a == b + 1),
 * and then for our last segment we'll take the rest of the elements and we know this has to be valid by our equation.
 *
 *
 * How should we come up with this in a contest?
 *
 * We should think about our greedy approaches, and think about how to test the range [x, y]. Then,
 * we can come up with the equation. Then, we can observe that the order of elements doesn't matter.
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
// const int MOD = 1'000'000'000 + 7;
const int MOD2 = 998'244'353;


void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    map<int, int> m;
    vector<int> b;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (m[a[i]] == 0) {
            b.push_back(a[i]);
        }
        m[a[i]]++;
    }

    sort(b.begin(), b.end());

    int l = 0;
    int curr = 0;
    int best_x = 0;
    int best_y = MAX;
    for (int i = 0; i < b.size(); i++) {
        curr += m[b[i]];
        while(curr >= ceil((n + k) / 2.0)) {
            // cout << b[i] << " " << b[l] << " " << curr << " " << ceil((n + k) / 2.0) << endl;
            int dist = b[i] - b[l];
            if (dist < best_y - best_x) {
                best_x = b[l];
                best_y = b[i];
            }

            curr -= m[b[l]];
            l++;
        }
    }

    vector<pii> ans;
    int in = 0, out = 0;
    l = 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (best_x <= a[i] && a[i] <= best_y) {
            in++;
        } else {
            out++;
        }

        if (in >= out + 1 && count < k - 1) {
            count++;
            ans.emplace_back(l, i);
            l = i + 1;
            in = 0;
            out = 0;
        }
    }

    ans.emplace_back(l, n - 1);

    cout << best_x << " " << best_y << endl;

    for (int i = 0; i < k; i++) {
        cout << ans[i].first + 1 << " " << ans[i].second + 1 << endl;
    }
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
