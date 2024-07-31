// #include <cstdio>

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

    vector<ll> give(n), rec(n);
    for (int i = 0; i < n; i++) {
        ll d = abs(a[i] - target);
        if (d == 0) {
            rec[i] = 0;
            give[i] = 0;
            continue;
        }

        bool start = false;
        bool end = false;
        int lsb = 0;
        int msb = 0;
        for (int j = 0; j < 31; j++) {
            bool e = d & (1 << j);
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
            rec[i] = msb + 1;
            give[i] = lsb;
        } else {
            rec[i] = lsb;
            give[i] = msb + 1;
        }

        // cout << i << " " << a[i] << " " << rec[i] << " " << give[i] << endl;
    }

    if (!works) {
        cout << "NO" << endl;
        return;
    }

    vector<int> freqr(31, 0);
    vector<int> freqg(31, 0);
    for (int i = 0; i < n; i++) {
        freqr[rec[i]]++;
        freqg[give[i]]++;
    }

    // cout << "HOLA" << endl;

    for (int i = 0; i < 31; i++) {
        // cout << i << " " << freqr[i] << " " << freqg[i] << endl;
        if (freqr[i] != freqg[i]) {
            works = false;
            break;
        }
    }

    if (!works) {
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