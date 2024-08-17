
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
const int MAX = 1e8;
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
    int n, q;
    cin >> n >> q;

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        int rep = 0;
        for (int j = 0; j < 2; j++) {
            if (s[j] == 'B') rep |= (1 << 3);
            else if (s[j] == 'G') rep |= (1 << 2);
            else if (s[j] == 'R') rep |= (1 << 1);
            else if (s[j] == 'Y') rep |= 1;
        }

        a[i] = rep;
    }

    vector<vector<int>> pre(16, vector<int>(n + 1, 0));

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < n; j++) {
            pre[i][j + 1] = pre[i][j] + (a[j] == i);
        }
    }

    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;

        int temp = max(x, y);
        x = min(x, y);
        y = temp;

        if (a[x] & a[y]) {
            cout << y - x << endl;
            continue;
        }

        vector<int> need;

        for (int j = 0; j < 4; j++) {
            if (!(a[x] & (1 << j))) continue;

            for (int k = 0; k < 4; k++) {
                if (!(a[y] & (1 << k))) continue;

                need.push_back((1 << j) | (1 << k));
            }
        }

        bool works = false;
        for (int j = 0; j < 4; j++) {;
            if (pre[need[j]][y + 1] - pre[need[j]][x] > 0) {
                works = true;
                break;
            }
        }

        if (works) {
            cout << y - x << endl;
            continue;
        }

        int best = MAX;

        for (int j = 0; j < 4; j++) {
            int l = y + 1, r = n - 1;
            int ans = MAX;
            while (l <= r) {
                int mid = l + (r - l) / 2;
                if (pre[need[j]][mid + 1] - pre[need[j]][y + 1] > 0) {
                    ans = mid;
                    r = mid - 1;
                } else l = mid + 1;
            }

            if (ans != MAX) best = min(best, ans - x + ans - y);

            ans = MAX;
            l = 0, r = x - 1;
            while (l <= r) {
                int mid = l + (r - l) / 2;
                if (pre[need[j]][x] - pre[need[j]][mid] > 0) {
                    ans = mid;
                    l = mid + 1;
                } else r = mid - 1;
            }

            if (ans != MAX) best = min(best, y - ans + x - ans);
        }

        if (best == MAX) {
            cout << -1 << endl;
        } else cout << best << endl;
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


    // solve();

    // /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    // */
}

