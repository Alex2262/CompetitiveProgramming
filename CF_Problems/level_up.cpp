// #include <cstdio>


/*
 * Problem takeaways:
 *
 * Lets observe a few things. First off, if we loop through all power levels and all possible
 * k values, we arrive at a time complexity of O(n log n) since we get a harmonic series of:
 * n/1 + n/2 + n/3 + ... + n/k --> n * (1 + 1/2 + 1/3 + ... 1/k). The maximum of k is n.
 *
 * Next, we observe that if we cannot reach a power level with a certain k, then for all higher k we are similarly
 * unable to reach the higher power level.
 *
 * So then in order to solve each query, if we can achieve a list for each k of all indexes where we level up,
 * it is simply a binary search for each query in around O(log(n / k)).
 *
 * To achieve this, we loop through each power level, and then loop through each k, such that we try and
 * binary search the index of a powerup using a range sum query.
 *
 * How do we range sum query? We use segment tree. For each element, we store a 1 in our segtree.
 * At the start of each new level, we remove the elements that are less than our current level from the segtree
 * (point update them to 0). Then, this range sum is valid.
 *
 * How should we solve this in contest?
 * The observations are decently important, but it is also just important to think hard about this problem and what
 * we can try to achieve. If we do not think about different loops and possibilites, we can never arrive at the idea
 * of a range sum query. But once we do, it's not too difficult.
 *
 *
 * Our final time complexity is O(n log^3(n) + q * log(log(n)))
 *
 * we get the q * log(log(n)) part because we perform a binary search on indices, and we have
 * on average log(n) indices because of the harmonic series.
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
#include <string.h>

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
const int MOD = 1'000'000'000 + 7;
// const int MOD2 = 998'244'353;

// Max N value
const int N = 2e5 + 10;
ll tree[N * 2];
int n;

// BUILD TREE
// O(n)
// Note that:
// 1. i << 1     == i * 2
// 2. i << 1 | 1 == i * 2 + 1
void build() {
    for (int i = n - 1; i > 0; i--) tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

// MODIFY TREE (single point)
// O(log(n))
// Note that:
// p ^ 1 ensures we add both child nodes
void modify_point(int p, int value) {
    p += n;
    tree[p] = value;
    for (; p > 1; p >>= 1) tree[p >> 1] = tree[p] + tree[p ^ 1];
}

// QUERY (range)
// O(log(n))
// sum on interval [l, r)
ll query_range(int l, int r) {
    l += n, r += n;
    ll res = 0;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res += tree[l++];
        if (r & 1) res += tree[--r]; // Remember that r is the excluded bound
    }

    return res;
}


void solve() {
    int q;
    cin >> n >> q;

    memset(tree, 0, sizeof(tree));

    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        tree[n + i] = 1;
    }

    build();

    map<ll, vector<int>> m;
    for (int i = 0; i < n; i++) m[a[i]].push_back(i);

    vector<vector<int>> inds(n);
    vector<bool> completed(n, false);

    for (int i = 0; i < n; i++) inds[i].push_back(i);

    // loop through the levels
    // skip level 0 since we know all inds there must be k
    for (int i = 1; i < n; i++) {

        // cout << "POWER " << i << endl;

        // we remove lower levels
        for (int j = 0; j < m[i].size(); j++) {
            modify_point(m[i][j], 0);
        }

        for (int j = 0; j < n; j++) {

            if (completed[j]) break;
            int prev_end = inds[j].back() + 1;

            int l = prev_end;
            int r = n;

            int k = j + 1;

            // we do a lowerbound b search
            while (l < r) {
                int mid = l + (r - l) / 2;
                ll range_sum = query_range(prev_end, mid + 1);

                if (range_sum >= k) r = mid;
                else l = mid + 1;
            }

            if (l >= n || l < prev_end) {
                completed[j] = true;
                break;
            }

            ll range_sum = query_range(prev_end, l + 1);
            // cout << range_sum << " " << inds[]
            if (range_sum < k) {
                completed[j] = true;
                break;
            }

            inds[j].push_back(l);

            // cout << "WHAT " << j << " " << i << " " << l << endl;
        }
    }

    for (int i = 0; i < q; i++) {
        int ind, x;
        cin >> ind >> x;
        ind--, x--;

        if (ind <= x) {
            cout << "YES" << endl;
            continue;
        }

        int lvl_ind = lower_bound(inds[x].begin(), inds[x].end(), ind) - inds[x].begin();

        if (lvl_ind + 1 > a[ind]) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
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
