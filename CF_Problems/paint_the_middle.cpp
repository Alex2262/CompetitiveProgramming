#pragma GCC optimize("O3,unroll-loops")
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
const int MOD = 1'000'000'000 + 7;
// const int MOD2 = 998'244'353;

// const int N = 3e5 + 5;

/*
 * We have to recognize that using a new range will add two elements that are c[i] = 0 if
 * the range is not connected with another range, and it will add one element that is c[i] = 0
 * if the range is part of another range.
 *
 * The point is that we track the number of c[i] = 0, and then do n - num(c[i]) to obtain our answer.
 *
 *
 *
 *
 *
 */


const int N = 2e5 + 10;
int tree[N * 2];
int sz;


void build() {
    for (int i = sz - 1; i > 0; i--) tree[i] = min(tree[i << 1], tree[i << 1 | 1]);
}

void modify_point(int p, int value) {
    p += sz;
    tree[p] = value;
    for (; p > 1; p >>= 1) tree[p >> 1] = min(tree[p], tree[p ^ 1]);
}

int query_range(int l, int r) {
    l += sz, r += sz;
    int res = MAX;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            res = min(res, tree[l]);
            l++;
        }
        if (r & 1) {
            r--;
            res = min(res, tree[r]);
        }
    }

    return res;
}



void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }

    vector<int> first(n, -1);
    for (int i = 0; i < n; i++) {
        if (first[a[i]] == -1) first[a[i]] = i;
    }

    vector<int> dp(n + 1, MAX);

    sz = n + 1;
    for (int i = 0; i < 2 * sz; i++) tree[i] = MAX;
    build();

    dp[0] = 0;
    modify_point(0, 0);

    for (int i = 0; i < n; i++) {
        int l = first[a[i]];

        if (l == i) {
            dp[i + 1] = min(dp[i + 1], dp[i] + 1);
            modify_point(i + 1, dp[i + 1]);
            continue;
        }

        dp[i + 1] = min(dp[i + 1], dp[l] + 2);

        int mid = query_range(l + 2, i + 1);
        if (mid != MAX) dp[i + 1] = min(dp[i + 1], mid + 1);

        modify_point(i + 1, dp[i + 1]);
    }

    cout << n - dp[n] << endl;
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

    solve();
}

