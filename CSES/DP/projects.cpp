
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
const int MOD = 1'000'000'000 + 7;

struct Project {
    ll a;
    ll b;
    ll c;
};


void solve() {
    int n;
    cin >> n;

    vector<Project> projects;

    for (int i = 0; i < n; i++) {
        ll a, b, c;
        cin >> a >> b >> c;

        projects.push_back({a, b, c});
    }

    sort(projects.begin(), projects.end(), [](auto& l, auto& r) {
        return l.b < r.b;
    });

    vector<ll> ends;
    ends.push_back(projects[0].b);
    for (int i = 1; i < n; i++) {
        if (projects[i].b != ends.back()) ends.push_back(projects[i].b);
    }

    vector<ll> dp(n + 1, 0);

    int j = 0;
    ll curr = projects[0].b;
    for (int i = 0; i < n; i++) {
        int ind = lower_bound(ends.begin(), ends.end(), projects[i].a) - ends.begin();
        ind--;
        // cout << i << " " << ind << " " << projects[i].a << " " << projects[i].b << " " << projects[i].c << endl;

        if (projects[i].b != curr) {
            curr = projects[i].b;
            j++;
            dp[j] = max(dp[j], dp[j - 1]);
        }

        if (ind < 0) {
            dp[j] = max(dp[j], projects[j].c);
            continue;
        }

        dp[j] = max(dp[j], projects[i].c + dp[ind]);

        // cout << i << " " << j << " " << dp[j] << endl;
    }

    ll best = 0;
    for (int i = 0; i <= n; i++) best = max(best, dp[i]);

    cout << best << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    */
}
