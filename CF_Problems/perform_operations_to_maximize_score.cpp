
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

/*
 *
 *
 *
 */



void solve() {
    ll n, k;
    cin >> n >> k;

    vector<ll> a(n);

    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];

    vector<pll> c(n);
    for (int i = 0; i < n; i++) {
        c[i].first = a[i];
        c[i].second = b[i];
    }

    sort(c.begin(), c.end(), greater<>());

    ll mx = c[0].first;
    ll mx2 = -1;
    int mx2_ind = 0;
    for (int i = 0; i < n; i++) {
        if (!c[i].second) continue;
        mx2 = c[i].first;
        mx2_ind = i;
        break;
    }

    ll med = c[(n + 1) / 2].first;

    // We cant modify anything
    if (mx2 == -1) {
        cout << mx + med << endl;
        return;
    }

    mx2 += k;

    vector<ll> case3;

    for (int i = 0; i < n; i++) {
        if (i == mx2_ind) continue;
        case3.push_back(c[i].first);
    }

    ll med3 = case3[n / 2];

    vector<pll> x;

    int count = 0;

    for (int i = 0; i < n; i++) {
        if (!c[i].second) continue;

        x.emplace_back(c[i].first, i);
        count++;

        if (count == (n + 1) / 2) {
            break;
        }
    }

    int num = 1;
    ll med2 = x.back().first;
    ll temp_k = k;
    int last = -1;

    for (int i = x.size() - 2; i >= 0; i--) {
        // cout << i << " " << med2 << endl;
        if (x[i].first == med2) {
            num++;
            continue;
        }

        ll need = (x[i].first - med2) * num;
        if (temp_k < need) {
            last = i;
            break;
        }

        temp_k -= need;
        num++;
        med2 = x[i].first;
    }

    ll med4 = med;
    int med4_ind = 0;
    for (int i = (n + 1) / 2; i < n; i++) {
        if (!c[i].second) continue;
        med4 = c[i].first;
        med4_ind = i;
        break;
    }

    ll im = c[(n + 1) / 2 - 1].first;

    // cout << med4 << " " << im << endl;
    med4 = min(med4 + k, im);


    // cout << num << " " << med2 << " " << temp_k << endl;

    med2 += temp_k / num;
    temp_k = temp_k % num;

    ll ans = mx + med;  // case 1

    ans = max(ans, mx + max(med2, med4)); // case 2

    ans = max(ans, mx2 + med3); // case 3

    // cout << mx << " " << mx2 << " " << med << " " << med2 << " " << med3 << endl;

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

