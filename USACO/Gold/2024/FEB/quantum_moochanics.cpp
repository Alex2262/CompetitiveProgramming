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
 *
 *
 *
 */

ull rand64(ull s) {
    s ^= s >> 12, s ^= s << 25, s ^= s >> 27;
    return s * 2685821657736338717LL;
}


ll pos(ll initial, ll speed, ll obs, bool right) {
    ll amt;

    if (obs & 1) amt = obs / 2 + 1;
    else amt = -obs / 2;

    if (!right) amt *= -1;

    ll d = amt * speed;

    return initial + d;
}


ll check(vector<ll>& p, vector<ll>& s, int i, int j) {
    ll upper = max((p[j] - p[i]) / (s[i] + s[j]), 4LL) * 2 + 2;

    ll l = 1, r = upper;
// 999999999999 999999999999
    ll ans = r;
    while (l <= r) {
        ll mid = l + (r - l) / 2;

        bool works = true;

        ll obs = mid * 2;
        if (i % 2 == 0) obs--;

        ll pos1 = pos(p[i], s[i], obs, i % 2 == 0);
        ll pos2 = pos(p[j], s[j], obs, j % 2 == 0);

        if (pos1 < pos2) works = false;

        // cout << i << " " << j << " " << mid << " " << pos1 << " " << pos2 << " " << works << endl;

        if (works) {
            r = mid - 1;
            ans = mid;
        } else l = mid + 1;
    }

    ll obs = ans * 2;
    if (i % 2 == 0) obs--;

    return obs;
}

void solve() {
    int n;
    cin >> n;

    vector<ll> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    vector<ll> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];


    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<>> pq;

    for (int i = 0; i < n - 1; i++) {
        ll curr = check(p, s, i, i + 1);
        pq.push({curr, i, i + 1});
    }

    vector<pii> nb(n);

    for (int i = 0; i < n; i++) {
        nb[i] = {i - 1, i + 1};
        if (i == 0) nb[i].first = -1;
        if (i == n - 1) nb[i].second = -1;
    }

    vector<ll> res(n, -1);

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        ll curr = top[0];
        ll i = top[1];
        ll j = top[2];

        if (res[i] != -1 || res[j] != -1) continue;

        res[i] = curr;
        res[j] = curr;

        int left = nb[i].first;
        int right = nb[j].second;

        if (left == -1 || right == -1) {
            if (left != -1) nb[left].second = -1;
            if (right != -1) nb[right].first = -1;
            continue;
        }

        nb[left].second = right;
        nb[right].first = left;

        if (left % 2 == right % 2) continue;
        pq.push({check(p, s, left, right), left, right});
    }

    string ss;

    for (int i = 0; i < n; i++) {
        ss += to_string(res[i]) + " \n"[i == n - 1];
    }

    cout << ss;
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

    multi_solve();
    // stress();
}



