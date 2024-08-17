
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

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    int w;
    cin >> w;

    vector<ll> a(w);
    for (int i = 0; i < w; i++) cin >> a[i];

    vector<ll> coeffs;

    vector<vector<ll>> diff(n + 1, vector<ll>(m + 1, 0));
    vector<vector<ll>> pre(n + 1, vector<ll>(m + 1, 0));
    for (int i = 0; i <= n - k; i++) {
        for (int j = 0; j <= m - k; j++) {
            diff[i][j]++;
            diff[i][j + k]--;
            diff[i + k][j]--;
            diff[i + k][j + k]++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pre[i + 1][j + 1] = pre[i][j + 1] + pre[i + 1][j] - pre[i][j] + diff[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            coeffs.push_back(pre[i + 1][j + 1]);
        }
    }

    sort(coeffs.begin(), coeffs.end(), greater<>());
    sort(a.begin(), a.end(), greater<>());

    ll ans = 0;
    for (int i = 0; i < w; i++) ans += coeffs[i] * a[i];

    cout << ans << endl;
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

    // /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    // */
}

