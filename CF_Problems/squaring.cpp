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

using pii = pair<int, int>;
using pll = pair<ll, ll>;

const ll LL_MAX = 9223372036854775807;
const int MAX = 2147483647;
const int CSES_MOD = 1'000'000'000 + 7;

void solve() {
    int n;
    cin >> n;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll curr = a[0];
    int pow_times = 0;
    ll ans = 0;

    bool works = true;

    for (int i = 1; i < n; i++) {
        ll x = a[i];

        if (x < curr) {
            if (x == 1) {
                works = false;
                break;
            }

            while (x < curr) {
                x *= x;
                pow_times++;
            }
        }

        else if (x > curr) {
            if (curr == 1) {
                pow_times = 0;
            } else {
                curr *= curr;
                while (x >= curr && pow_times > 0) {
                    curr *= curr;
                    pow_times--;
                }
            }
        }

        curr = a[i];
        ans += pow_times;
    }

    if (!works) cout << -1 << endl;
    else cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //solve();

    // /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    // */
}