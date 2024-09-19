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
// const int MOD = 1'000'000'000 + 7;
const int MOD2 = 998'244'353;

// const int N = 3e5 + 5;

/*
 *
 *
 *
 *
 *
 */


const int N = 3e5 + 5;
int tree_min[N * 2];
int tree_max[N * 2];

int n;

void build_min() {
    for (int i = n - 1; i > 0; i--) tree_min[i] = min(tree_min[i << 1], tree_min[i << 1 | 1]);
}

void modify_point_min(int p, int value) {
    p += n;
    tree_min[p] = value;
    for (; p > 1; p >>= 1) tree_min[p >> 1] = min(tree_min[p], tree_min[p ^ 1]);
}

int query_range_min(int l, int r) {
    l += n, r += n;
    int res = MAX;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            res = min(res, tree_min[l]);
            l++;
        }
        if (r & 1) {
            r--;
            res = min(res, tree_min[r]);
        }
    }

    return res;
}

void build_max() {
    for (int i = n - 1; i > 0; i--) tree_max[i] = max(tree_max[i << 1], tree_max[i << 1 | 1]);
}

void modify_point_max(int p, int value) {
    p += n;
    tree_max[p] = value;
    for (; p > 1; p >>= 1) tree_max[p >> 1] = max(tree_max[p], tree_max[p ^ 1]);
}

int query_range_max(int l, int r) {
    l += n, r += n;
    int res = -1;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            res = max(res, tree_max[l]);
            l++;
        }
        if (r & 1) {
            r--;
            res = max(res, tree_max[r]);
        }
    }

    return res;
}

void solve() {
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int i = 0; i < n; i++) {
        tree_min[i + n] = a[i];
        tree_max[i + n] = a[i];
    }

    build_max();
    build_min();

    vector<int> count(n, 0);

    set<int> s;
    vector<int> ends(n + 1, 0);
    vector<int> stop(n, 0);

    for (int i = n - 1; i >= 0; i--) {
        if (s.find(a[i]) == s.end()) {
            ends[a[i]] = i;
            stop[i] = 1;
        }

        s.insert(a[i]);
        count[i] = s.size();
    }

    vector<vector<int>> inds(n + 1);
    for (int i = 0; i < n; i++) {
        inds[a[i]].push_back(i);
    }

    vector<int> res;
    int ind = 0;

    int l = 0;
    int r = 0;

    set<int> used;

    while (r < n) {

        while (!stop[r]) {
            if (r >= n - 1) break;
            r++;
        }

        int rem;

        if (ind % 2 == 0) {
            rem = query_range_max(l, r + 1);
        } else {
            rem = query_range_min(l, r + 1);
        }

        if (rem == -1 || rem == MAX) break;

        res.push_back(rem);

        bool found = false;

        for (int j : inds[rem]) {
            if (!found && j >= l && j <= r) {
                found = true;
                l = j + 1;
            }

            modify_point_min(j, MAX);
            modify_point_max(j, -1);
        }

        stop[ends[rem]] = 0;
        used.insert(rem);

        ind++;
    }

    cout << res.size() << endl;
    string st = to_string(res[0]);
    for (int i = 1; i < res.size(); i++) st += " " + to_string(res[i]);
    cout << st << endl;
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

    // ios_base::sync_with_stdio(false);
    // cin.tie(nullptr);

    // solve();
    multi_solve();
}




