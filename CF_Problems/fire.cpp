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

void solve() {
    int n;
    cin >> n;

    // vector<int> t(n);
    // vector<int> d(n);
    // vector<int> p(n);

    vector<array<int, 4>> a(n);

    for (int i = 0; i < n; i++) {
        // cin >> t[i] >> d[i] >> p[i];
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        a[i][3] = i;
    }

    // int mx = *max_element(d.begin(), d.end()) + 50;

    sort(a.begin(), a.end(), [](auto l, auto r){
        return l[1] < r[1] || l[1] == r[1] && l[0] < r[0];
    });

    int mx = 2100;

    vector<pair<int, vector<int>>> dp(mx, {-MAX, {}});

    dp[0] = {0, {}};

    for (int i = 0; i < n; i++) {
        vector<pair<int, vector<int>>> ndp = dp;

        for (int j = 0; j < a[i][1] - a[i][0]; j++) {
            if (dp[j].first == -MAX) continue;

            if (dp[j].first + a[i][2] > ndp[j + a[i][0]].first) {
                ndp[j + a[i][0]].first = dp[j].first + a[i][2];
                ndp[j + a[i][0]].second = dp[j].second;
                ndp[j + a[i][0]].second.push_back(i);
            }
        }

        dp = ndp;
    }

    int bi = 0;
    for (int i = 0; i < mx; i++) {
        if (dp[i].first > dp[bi].first) bi = i;
    }

    cout << dp[bi].first << endl;

    vector<int> used = dp[bi].second;

    cout << used.size() << endl;

    for (int i = 0; i < used.size(); i++) {
        cout << a[used[i]][3] + 1 << " \n"[i == used.size() - 1];
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


