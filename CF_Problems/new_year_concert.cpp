#pragma GCC optimize("O2,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

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
const ll MOD = 1'000'000'000 + 7;
// const ll MOD = 998'244'353;


/*
 *
 *
 *
 */


ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, (a % b));
}

const int MSZ = 2e5 + 5;
ll tree[MSZ * 2];
int sz;


ll op(ll a, ll b) {
    if (a == LL_MAX) return b;
    if (b == LL_MAX) return a;
    return gcd(a, b);
}

void build() {
    for (int i = sz - 1; i > 0; i--) tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
}

void modify_point(int p, ll value) {
    p += sz;
    tree[p] = value;
    for (; p > 1; p >>= 1) tree[p >> 1] = op(tree[p], tree[p ^ 1]);
}

ll query_range(int l, int r) {
    l += sz, r += sz;
    ll res = LL_MAX;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            res = op(res, tree[l]);
            l++;
        }

        if (r & 1) {
            r--;
            res = op(res, tree[r]);
        }
    }

    return res;
}

void solve() {
    int n;
    cin >> n;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int need = 0;
    int left = 0;

    vector<ll> res(n);

    sz = n;

    for (int i = 0; i < n; i++) {
        tree[i] = LL_MAX;
        tree[i + n] = a[i];
    }

    build();

    for (int i = 0; i < n; i++) {
        bool works = true;

        int l = left, r = i;

        // cout << "I " << i << endl;

        while (l <= r) {
            int mid = l + (r - l) / 2;

            ll curr = query_range(mid, i + 1);

            ll len = i - mid + 1;

            if (curr == len) {
                works = false;
                break;
            }

            if (curr < len) {
                l = mid + 1;
            } else r = mid - 1;
        }

        if (!works) {
            need++;
            left = i + 1;

            res[i] = need;
            continue;
        }

        res[i] = need;
    }

    string ans;
    for (int i = 0; i < n; i++) ans += to_string(res[i]) + " \n"[i == n - 1];

    cout << ans;
}

void multi_solve() {
    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        solve();
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
    // multi_solve();
}


