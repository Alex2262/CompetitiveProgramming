// #include <cstdio>

/*
 * Problem takeaways:
 * If there are equations involved in the problem, we should write out these equations and see if there
 * is anything we can notice from them. For example, for the hard part of this problem,
 * we need to recognize that for values that are powers of 2, if they only give/receive, it is one power less than
 * if they had to give and receive.
 *
 * Thus, we can figure out what operations are possible in this problem.
 * Then, another important observation is that we loop across the descending bits. That is because once we resolve
 * higher bits, then we don't need to worry about modifying them anymore.
 *
 * To solve this problem in a contest:
 * 1. Reduce the problem to certain equations
 * 2. Make observations about these equations, and the variables in these equations
 * 3. Reduce the problem even more with these observations
 * 4. Take this reduced problem, and find an efficient way to solve it using all observations you have made.
 *
 *
 * We can also simplify this code next time by brute forcing to find the important bits, since that's just
 * O(max_bits^2), so O(30^2), which isn't too much. But what we did here works.
 */

#include <deque>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;
using ll = long long;

const ll LL_MAX = 9223372036854775807;
const int MAX = 2147483647;
const int MOD = 1'000'000'000 + 7;

void solve() {
    int n;
    cin >> n;

    vector<ll> a(n);
    ll tot = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        tot += a[i];
    }

    if (tot % n != 0) {
        cout << "NO" << endl;
        return;
    }

    ll target = tot / n;

    bool works = true;

    vector<ll> give(n), rec(n), only_give(n, 100), only_rec(n, 100);
    for (int i = 0; i < n; i++) {
        ll d = abs(a[i] - target);

        rec[i] = 50;
        give[i] = 50;

        if (d == 0) {
            continue;
        }

        bool start = false;
        bool end = false;
        ll lsb = 0;
        ll msb = 0;
        for (int j = 0; j <= 31; j++) {
            ll e = d & (1LL << j);
            if (start) {
                if (!e) {
                    msb = j - 1;
                    end = true;
                    start = false;
                }
            } else if (end) {
                if (e) {
                    works = false;
                    break;
                }
            } else {
                if (e) {
                    lsb = j;
                    start = true;
                }
            }
        }

        if (!works) break;

        if (a[i] < target) {
            // power of 2
            if (lsb == msb) {
                only_rec[i] = msb;
            } else {
                rec[i] = msb + 1;
                give[i] = lsb;
            }
        } else {
            // power of 2
            if (lsb == msb) {
                only_give[i] = msb;
            } else {
                rec[i] = lsb;
                give[i] = msb + 1;
            }
        }

        // cout << i << " " << a[i] << " " << rec[i] << " " << give[i] << " " << only_rec[i] << " " << only_give[i] << endl;
    }

    if (!works) {
        cout << "NO" << endl;
        return;
    }

    vector<ll> freqr(32, 0);
    vector<ll> freqg(32, 0);
    vector<ll> only_freqr(32, 0);
    vector<ll> only_freqg(32, 0);
    for (int i = 0; i < n; i++) {
        if (rec[i] < 32) freqr[rec[i]]++;
        if (give[i] < 32) freqg[give[i]]++;
        if (only_rec[i] < 32) only_freqr[only_rec[i]]++;
        if (only_give[i] < 32) only_freqg[only_give[i]]++;
    }

    for (int i = 31; i >= 0; i--) {

        // We know that we always have to sum this since they either have the option:
        // 1. Only receive or only give (when a[i] > target)
        // 2. Receive i + 1 and give i, or receive i and give i + 1 (when a[i] > target)
        //
        // Since we already established equality in the higher bits,
        // If we do not choose option 1, then we will end up modifying the higher bits

        // Remember, we have to choose one of these options, otherwise those values will not
        // reach target if they do not give/receive correctly.
        freqr[i] += only_freqr[i];
        freqg[i] += only_freqg[i];
        if (i == 0) continue;

        if (freqr[i] == freqg[i]) continue;

        // Use the lower ones to help
        // Here is where option 2 is necessary.
        // We use option 2 to help us.
        if (freqr[i] < freqg[i]) {
            ll amt = freqg[i] - freqr[i];
            only_freqr[i - 1] -= amt;
            freqg[i - 1] += amt;

            if (only_freqr[i - 1] < 0) {
                works = false;
                break;
            }
        }

        else {
            ll amt = freqr[i] - freqg[i];
            only_freqg[i - 1] -= amt;
            freqr[i - 1] += amt;

            if (only_freqg[i - 1] < 0) {
                works = false;
                break;
            }
        }
    }

    if (!works || freqr[0] != freqg[0]) {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // solve();

    // /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    // */
}
