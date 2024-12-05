#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// ~9 * 10 ^ 18
const ll LL_MAX = 9'223'372'036'854'775'807;

// ~2 * 10 ^ 9
const int MAX = 2'147'483'647;
// const ll MOD = 1'000'000'000 + 7;
const ll MOD = 998'244'353;



/*
 *
 *
 *
 */

const int BLOCK_SIZE = 450;

struct Query {
    int l, r, idx;
};

bool cmp(Query& a, Query& b) {
    int a_block = a.l / BLOCK_SIZE;
    int b_block = b.l / BLOCK_SIZE;

    if (a_block != b_block) return a_block < b_block;

    if (a_block & 1) return a.r < b.r;
    return a.r > b.r;
}


void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> temp(n);
    for (int i = 0; i < n; i++) temp[i] = a[i];

    sort(temp.begin(), temp.end());

    int w = 0;
    vector<int> b(n);
    map<int, int> conv;
    for (int i = 0; i < n; i++) {
        if (i > 0 && temp[i] > temp[i - 1]) w++;
        conv[temp[i]] = w;
    }

    for (int i = 0; i < n; i++) b[i] = conv[a[i]];

    vector<Query> qs;

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        qs.push_back({l, r, i});
    }

    vector<int> ans(qs.size());

    sort(qs.begin(), qs.end(), cmp);

    vector<int> ma(n + 1, 0);

    int curr = 0;

    auto add = [&](int idx) {
        if (ma[b[idx]] == 0) curr++;
        ma[b[idx]]++;
    };

    auto rem = [&](int idx) {
        ma[b[idx]]--;
        if (ma[b[idx]] == 0) curr--;
    };

    int curr_l = 0;
    int curr_r = -1;

    for (Query query : qs) {
        while (curr_l > query.l) add(--curr_l);
        while (curr_r < query.r) add(++curr_r);
        while (curr_l < query.l) rem(curr_l++);
        while (curr_r > query.r) rem(curr_r--);

        ans[query.idx] = curr;
    }

    for (auto e : ans) cout << e << endl;
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
    // stress();
}
