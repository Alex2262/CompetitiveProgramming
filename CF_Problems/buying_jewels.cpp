
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

// const int N = 3e5 + 5;


void solve() {
    ll n, k;
    cin >> n >> k;

    if (k > n) {
        cout << "NO" << endl;
        return;
    }

    if (k == n) {
        cout << "YES" << endl;
        cout << 1 << endl;
        cout << 1 << endl;
        return;
    }

    if (k == 1) {
        cout << "YES" << endl;
        cout << 1 << endl;
        cout << n << endl;
        return;
    }

    // a == n - k + 1 and b == 1
    // If n == 500 and k == 200, then 500 - 200 + 1 = 301. 500 - 301 = 199. 1 + 199 = 200!
    // n - (n - k + 1) == n - n + k - 1 == k - 1

    ll a = n - k + 1;
    ll b = 1;
    if ((n / a) + n - a != k) {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;
    cout << 2 << endl;
    cout << a << " " << b << endl;
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

