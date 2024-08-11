
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


const int N = 2e5 + 5;
int tree[N * 2];
int n;

// BUILD TREE
// O(n)
// Note that:
// 1. i << 1     == i * 2
// 2. i << 1 | 1 == i * 2 + 1
void build() {
    for (int i = n - 1; i > 0; i--) tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

// MODIFY TREE (range)
// O(log(n))
// on range [l, r)
void modify_range(int l, int r, int value) {
    l += n, r += n;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) tree[l++] += value;
        if (r & 1) tree[--r] += value;
    }
}

// PUSH
void push() {
    for (int i = 1; i < n; i++) {
        tree[i << 1] += tree[i];
        tree[(i << 1) | 1] += tree[i];
        tree[i] = 0;
    }
}


void solve() {
    cin >> n;

    memset(tree, 0, sizeof(tree));

    vector<ll> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];

    ll k;
    cin >> k;

    vector<int> mins(n, -1);
    vector<int> v;

    ll curr = LL_MAX;
    int best_idx = n;
    for (int i = n - 1; i >= 0; i--) {
        if (c[i] < curr) {
            curr = c[i];
            best_idx = i;
            v.push_back(best_idx);
        }

        mins[i] = best_idx;
    }

    reverse(v.begin(), v.end());

    for (int i = 0; i < v.size() - 1; i++) {
        while (true) {
            ll curr_ops = k / c[v[i]];
            ll next_ops = k / c[v[i + 1]];

            if (curr_ops <= next_ops) break;

            // cout << v[i] << " " << v[i + 1] << endl;

            k -= (curr_ops - next_ops) * c[v[i]];
            modify_range(0, v[i] + 1, curr_ops - next_ops);
        }
    }

    ll curr_ops = k / c[v.back()];
    modify_range(0, v.back() + 1, curr_ops);
    push();

    // modify_range(0, 1, 10);

    // cout << "ANS" << endl;

    string s = to_string(tree[n]);
    for (int i = 1; i < n; i++) s += " " + to_string(tree[n + i]);
    cout << s << endl;
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

    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}

