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


ll bin_exp(ll x, ll y) {
    ll res = 1;
    x = x % MOD2;
    while (y > 0) {
        if (y & 1) res = (res * x) % MOD2;
        y = y >> 1;
        x = (x * x) % MOD2;
    }
    return res;
}

ll mod_inverse(ll n) {
    return bin_exp(n, MOD2 - 2);
}


const int K = 2;

struct Vertex {
    int next[K];
    ll cnt = 0;
    bool output = false;

    Vertex() {
        fill(begin(next), end(next), -1);
    }
};

vector<Vertex> trie;

void add_int(int x) {

    int v = 0;

    trie[v].cnt++;

    for (int i = 29; i >= 0; i--) {
        bool b = (1 << i) & x;

        if (trie[v].next[b] == -1) {
            trie[v].next[b] = trie.size();
            trie.emplace_back();
        }

        v = trie[v].next[b];
        trie[v].cnt++;
    }

    trie[v].output = true;
}

void rec(int v, int k, ll& ans) {

    // they are the same number
    if (trie[v].next[0] == -1 && trie[v].next[1] == -1) {
        ll ind = k;
        ll amt = trie[v].cnt * trie[v].cnt;

        // cout << "E " << v << " " << k << " " << amt << endl;

        ans = (ans + ((ind + 1) * amt)) % MOD2;
        return;
    }

    // one has a 0 bit and other is 1 bit
    if (trie[v].next[0] != -1 && trie[v].next[1] != -1) {
        ll ind = k;
        ll amt = trie[trie[v].next[0]].cnt * trie[trie[v].next[1]].cnt;

        // cout << "B " << v << " " << k << " " << amt << endl;

        ans = (ans + (2 * ((ind + 1) / 2) + 1) * amt) % MOD2;
        ans = (ans + (2 * ((ind / 2) + 1))     * amt) % MOD2;
    }

    // only 0 bit
    if (trie[v].next[0] != -1) {
        rec(trie[v].next[0], k, ans);
    }

    // only 1 bit
    if (trie[v].next[1] != -1) {
        rec(trie[v].next[1], k + 1, ans);
    }
}

void solve() {
    trie.clear();
    trie.emplace_back();

    ll n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) add_int(a[i]);

    ll ans = 0;
    rec(0, 0, ans);

    ans = (ans * mod_inverse(n)) % MOD2;
    ans = (ans * mod_inverse(n)) % MOD2;

    cout << ans << endl;

    // Two get the number of turns in one game:
    // We count the number of matching 1s in both numbers until it reaches a 0 in either number.
    // If the 0 is in the first number and not in second number, then
    // turns = 2 * floor((ind + 1) / 2) + 1
    // If the 0 is in the second number and not in first number, then
    // turns = 2 * (floor(ind / 2) + 1)
    // If 0 is in both numbers:
    // turns = min(both formulas above), or more simply we can notice: ind + 1

    // 1. 2 * floor((ind + 1) / 2) + 1
    // 2. 2 * (floor(ind / 2) + 1)
    // 3. ind + 1
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

