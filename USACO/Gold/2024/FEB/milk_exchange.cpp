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
// const ll MOD = 1'000'000'000 + 7;
// const ll MOD = 998'244'353;

const ll MOD = 3359232;


/*
 * Solved this one completely myself!
 *
 * I just drew out testcases and made certain observations, and then the rest was just
 * implementation and bug fixing. Had to write a stress test to catch errors, but got 23/23 with it, so
 * that was nice :)
 *
 *
 */

ull rand64(ull s) {
    s ^= s >> 12, s ^= s << 25, s ^= s >> 27;
    return s * 2685821657736338717LL;
}

void solve() {
    int n;
    cin >> n;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<ll> b;
    for (int i = 1; i < n; i++) b.push_back(a[i]);
    for (int i = 0; i < n; i++) b.push_back(a[i]);

    int m = static_cast<int>(b.size());

    ll sum = accumulate(a.begin(), a.end(), 0LL);

    // we will store;
    // curr value, prev index, start index
    priority_queue<array<ll, 3>> pq;

    vector<ll> diff(n + 1, 0);

    for (int i = m - 1; i >= 0; i--) {
        vector<array<ll, 3>> add;

        while (!pq.empty()) {
            auto& top = pq.top();

            ll curr = top[0];
            int prev = top[1];
            int start = top[2];

            if (curr < b[i]) break;

            pq.pop();

            int r = prev;
            int l = i + 1;

            int tot = r - l + 1;
            int op_start = start - r;
            int op_end = op_start + tot;

            ll amt = b[prev] - b[start];
            diff[op_start] += amt;
            diff[op_end] -= amt;

            if (b[i] <= b[start]) continue;

            add.push_back({b[i], i, start});
        }

        for (auto& e : add) pq.push(e);

        if (i >= n - 2 && i < m - 1) {
            if (b[i] <= b[i + 1]) continue;
            pq.push({b[i], i, i + 1});
        }
    }

    while (!pq.empty()) {
        auto& top = pq.top();

        ll curr = top[0];
        int prev = top[1];
        int start = top[2];

        pq.pop();

        int r = prev;
        int l = 0;

        int tot = r - l + 1;

        if (tot <= 0) continue;

        int op_start = start - r;
        int op_end = op_start + tot;

        ll amt = b[prev] - b[start];
        diff[op_start] += amt;
        diff[op_end] -= amt;
    }

    vector<ll> pre(n + 2, 0);
    for (int i = 0; i < n + 2; i++) {
        pre[i + 1] = pre[i] + diff[i];
    }

    vector<ll> ans(n);

    ll curr = sum;
    for (int i = 2; i < n + 2; i++) {
        curr -= pre[i];
        ans[i - 2] = curr;
        cout << curr << endl;
    }

    // return ans;
}


/*
vector<ll> brute(int n, vector<ll> a) {
    vector<ll> ans(n);

    ll curr = accumulate(a.begin(), a.end(), 0LL);

    for (int t = 0; t < n; t++) {
        ll start = a[n - 1];
        for (int i = n - 1; i >= 0; i--) {
            ll prev = start;
            if (i > 0) prev = a[i - 1];

            if (prev > a[i]) {
                curr -= (prev - a[i]);
                prev = a[i];
            }

            a[i] = prev;
        }

        ans[t] = curr;
    }

    return ans;
}


void stress() {
    int n = 100;
    int test = 1000;

    int max_val = 19;

    ull s = 2354;

    for (int t = 0; t < test; t++) {

        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            s = rand64(s);
            s %= max_val;

            s += 1;

            s += 2;
            a[i] = s;
        }

        vector<ll> b_ans = brute(n, a);
        vector<ll> s_ans = solve(n, a);

        bool works = true;
        for (int i = 0; i < n; i++) if (b_ans[i] != s_ans[i]) works = false;

        if (!works) {
            for (int i = 0; i < n; i++) {
                cout << "A " << a[i] << " " << b_ans[i] << " " << s_ans[i] << endl;
            }
            break;
        }
    }

    cout << "TESTS PASSED" << endl;
}
 */

void multi_solve() {
    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        // solve();
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



