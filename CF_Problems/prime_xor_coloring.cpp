// #include <cstdio>

/*
 * Problem takeaways:
 *
 * This problem is quite difficult but you have to make some observations.
 * 1. The graph formed will basically be bipartite because evens will always be connected to odds and odds to evens,
 * except for when odds are connected to odds (xor is = 2),
 * and also except for when evens are connected to evens (xor is = 2)
 *
 * Based on this observation, we have to notice that the maximum colors necessary is 4. Why? In each group, we will need
 * 2 colors for the case of even-even or odd-odd. We also have 2 such groups, so 2*2 = 4.
 *
 * 2. We also know we have 4 colors, but an important observation that can even be used to skip step 1. is that
 * if we have 4 colors that alternate through 0 ... n, then if two numbers that are mod 4 ever xor each other
 * (in this case they will have the same color), their xor can never be prime. So this always works out,
 * and this also allows us to construct the solution.
 *
 *
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

#define popcount    __builtin_popcount
#define popcount_ll __builtin_popcountll
#define lsb         __builtin_ctz
#define lsb_ll      __builtin_ctzll
#define msb         __builtin_clz
#define msb_ll      __builtin_clzll
#define parity      __builtin_parity

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

const ll LL_MAX = 9223372036854775807;
const int MAX = 2147483647;
const int MOD = 1'000'000'000 + 7;


void solve() {
    int n;
    cin >> n;

    if (n == 1) cout << "1\n1\n";
    else if (n == 2) cout << "2\n1 2\n";
    else if (n == 3) cout << "2\n1 2 2\n";
    else if (n == 4) cout << "3\n1 2 2 3\n";
    else if (n == 5) cout << "3\n1 2 2 3 3\n";
    else {
        cout << 4 << endl;
        string s = "1";
        for (int i = 0; i < n - 1; i++) {
            s += " " + to_string((i + 1) % 4 + 1);
        }

        cout << s << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // solve();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}