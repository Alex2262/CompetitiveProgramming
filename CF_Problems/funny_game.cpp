// #include <cstdio>

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


void solve() {
    int n;
    cin >> n;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<pii> edge;

    vector<bool> used(n, false);

    // we can prove that if we are at operation i, then we have i + 1 vertices.
    // this means that there must exist two elements in this i + 1 vertices which share the same value mod i,
    // and this is by the pigeonhole principle.
    // so simply by looping from n - 1 --> 1, we can construct a valid solution

    for (int i = n - 1; i >= 1; i--) {
        vector<int> m(n, -1);
        for (int j = 0; j < n; j++) {
            if (used[j]) continue;
            if (m[a[j] % i] != -1) {
                edge.push_back({m[a[j] % i], j});
                used[j] = true;
                break;
            }
            m[a[j] % i] = j;
        }
    }

    cout << "YES" << endl;

    reverse(edge.begin(), edge.end());

    for (auto p : edge) {
        cout << p.first + 1 << " " << p.second + 1 << endl;
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

    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}

