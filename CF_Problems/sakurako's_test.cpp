#pragma GCC optimize("O3,unroll-loops")
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
const int MOD = 1'000'000'000 + 7;
// const int MOD2 = 998'244'353;

// const int N = 3e5 + 5;

/*
 * We can easily first recognize that optimally all elements should be a[i] % x.
 * However doing this and then sorting the array for each x would be way too slow.
 *
 * We need to recognize this idea that we are able to test for a fixed median if it works by
 * adding the number of elements within [x * i, x * i + median) , since these elements would be < median
 * when % by x. Interestingly, this would turn out to be O(n / x), which becomes a harmonic sequence across all x
 * since you can just compute each distinct x value. We arrive here with O(log n)
 *
 * Then, we just binary search on the median in O(log n) for each x value, and we arrive at
 * O(log^2 n).
 *
 * The most important idea is to ask, if we fix a median and fix x, then how can we see if the median works?
 * We understand that everything should be a[i] % x, but then extend this into checking the actual ranges.
 *
 */


void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> cnt(n + 1, 0);
    for (int i = 0; i < n; i++) cnt[a[i]]++;

    vector<int> pre(n + 2, 0);
    for (int i = 0; i <= n; i++) {
        pre[i + 1] = pre[i] + cnt[i];
    }


    vector<int> x(q);
    for (int i = 0; i < q; i++) cin >> x[i];

    vector<int> res(n + 1, -1);

    res[0] = 0;
    res[1] = 0;

    for (int i = 0; i < q; i++) {
        if (res[x[i]] != -1) continue;

        int l = 0, r = n;
        int ans;

        while (l <= r) {
            int mid = l + (r - l) / 2;

            ll c = 0;
            int j = 0;
            while (true) {
                if (j * x[i] > n) break;
                int end = min(n + 1, j * x[i] + mid + 1);

                // cout << j * x[i] << " " << end << " " << mid << endl;
                c += pre[end] - pre[j * x[i]];
                j++;
            }

            if (c >= n / 2 + 1) {
                ans = mid;
                r = mid - 1;
            } else l = mid + 1;
        }

        res[x[i]] = ans;
    }

    string s;
    for (int i = 0; i < q; i++) {
        s += to_string(res[x[i]]) + " \n"[i == n - 1];
    }

    cout << s;

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

