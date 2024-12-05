
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

const int BLOCK_SIZE = 300;

struct Query {
    int l, r, idx;
};

// In odd blocks, sort the right index in ascending order
// In even blocks, sort the right index in descending order
// This minimizes movement of the right pointer
bool cmp(Query& a, Query& b) {
    int a_block = a.l / BLOCK_SIZE;
    int b_block = b.l / BLOCK_SIZE;

    if (a_block != b_block) return a_block < b_block;

    if (a_block & 1) return a.r < b.r;
    return a.r > b.r;
}


void solve() {
    int n, m;
    ll k;
    cin >> n >> m >> k;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<ll> pre(n + 1, 0);
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] ^ a[i];

    vector<Query> qs;

    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        qs.push_back({l, r, i});
    }

    vector<ll> ans(qs.size());

    sort(qs.begin(), qs.end(), cmp);

    unordered_map<ll, ll> ma;

    ma[0] = 1;
    ll curr = 0;

    auto add_l = [&](int idx) {
        curr += ma[pre[idx] ^ k];
        ma[pre[idx]]++;
    };

    auto add_r = [&](int idx) {
        curr += ma[pre[idx + 1] ^ k];
        ma[pre[idx + 1]]++;
    };

    auto rem_l = [&](int idx) {
        ma[pre[idx]]--;
        curr -= ma[pre[idx] ^ k];
    };

    auto rem_r = [&](int idx) {
        ma[pre[idx + 1]]--;
        curr -= ma[pre[idx + 1] ^ k];
    };

    int curr_l = 0;
    int curr_r = -1;

    for (Query query : qs) {
        // cout << "PROCESSING " << query.l << " " << query.r << endl;
        while (curr_l > query.l) {
            curr_l--;
            add_l(curr_l);
        }

        while (curr_r < query.r) {
            curr_r++;
            add_r(curr_r);
        }

        while (curr_l < query.l) {
            rem_l(curr_l);
            curr_l++;
        }

        while (curr_r > query.r) {
            rem_r(curr_r);
            curr_r--;
        }

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

