
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


#define lsb         __builtin_ctz
#define msb         __builtin_clz


void solve() {
    int n, k;
    cin >> n >> k;

    int m = msb(k);
    int l = lsb(k);

    vector<int> a;

    int max_bits = 10;


    for (int i = 0; i < max_bits; i++) {
        if (i == 1) continue;
        a.push_back(1 << i);
    }

    vector<bool> dp((1 << max_bits) + 1, false);
    dp[0] = true;

    for (int i = 0; i < max_bits; i++) {
        if (i == 4) continue;
        for (int j = (1 << max_bits) - 1; j >= 0; j--) {
            if (dp[j]) dp[j + (1 << i)] = true;
        }
    }

    for (int i = 0; i < (1 << max_bits); i++) {
        if (dp[i]) cout << i << " IN" << endl;
        else cout << i << " OUT" << endl;
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

