// #include <cstdio>

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
    int n, m, q;
    cin >> n >> m >> q;

    string s;
    cin >> s;

    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = s[i] - '0';

    int num1 = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 1) num1++;
    }

    int block_size = 256;
    vector<int> all_weights(n, MAX);
    vector<int> blocks(block_size, MAX);

    for (int i = 0; i < n; i++) {
        blocks[i / block_size] = min(blocks[i / block_size], all_weights[i]);
    }

    vector<pii> t;
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;

        int c_l = l / block_size, c_r = r / block_size;

        int weight = i;

        // Range is contained in the same block
        if (c_l == c_r) {
            for (int j = l; j <= r; j++) all_weights[j] = min(all_weights[j], weight);
        }

        else {
            for (int j = l; j < (c_l + 1) * block_size; j++) all_weights[j] = min(all_weights[j], weight);
            for (int j = c_l + 1; j < c_r; j++) blocks[j] = min(blocks[j], weight);
            for (int j = c_r * block_size; j <= r; j++) all_weights[j] = min(all_weights[j], weight);
        }
    }

    for (int i = 0; i < n; i++) {
        a[i] = min(a[i], blocks[i / block_size]);
    }

    vector<vector<int>> mo(m + 1, vector<int>());
    for (int i = 0; i < n; i++) {
        mo[all_weights[i]].push_back(i);
    }

    vector<int> order;
    for (int i = 0; i < m + 1; i++) {
        for (int e : mo[i]) order.push_back(e);
    }

    vector<int> back_order(n);
    int curr_num = 0;
    for (int i = 0; i < n; i++) {
        back_order[a[i]] = curr_num;
        curr_num++;
    }

    int ops = 0;
    int used = num1;
    for (int i = 0; i < n && used > 0; i++) {
        if (a[order[i]] == 0) ops++;
        used--;
    }

    for (int i = 0; i < n; i++) {
        cout << i << " " << order[i] << endl;
    }

    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        x--;

        if (back_order[x] < num1) {
            if (a[x] == 0) ops--;
            else ops++;
        }

        if (a[x] == 0) {
            num1++;
            if (a[order[num1 - 1]] == 0) ops++;
        }

        if (a[x] == 1) {
            if (num1 > 0 && s[order[num1 - 1]] == 0) ops++;
            num1--;
        }

        a[x] ^= 1;
        cout << ops << endl;
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


    solve();

    /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
     */
}

