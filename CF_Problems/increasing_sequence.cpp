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
    for (int i = 0; i < n; i++) cin >> a[i];

    int add = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == i + 1 + add) add++;
    }

    cout << n + add << endl;
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