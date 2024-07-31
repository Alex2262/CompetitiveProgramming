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

    vector<int> freq(51, 0);

    vector<set<int>> vs(n);

    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;

        for (int j = 0; j < k; j++) {
            int s;
            cin >> s;

            freq[s]++;

            vs[i].insert(s);
        }
    }

    vector<vector<int>> rem(51, vector<int>(51));

    for (int i = 0; i <= 50; i++) {
        if (freq[i] == 0) continue;

        for (int j = 0; j < n; j++) {
            if (vs[j].find(i) != vs[j].end()) {
                for (auto& e : vs[j]) {
                    rem[i][e]++;
                }
            }
        }
    }

    int tot = 0;
    int best = MAX;
    for (int i = 0; i <= 50; i++) {
        if (freq[i] == 0) continue;
        tot++;
        int num = 0;
        for (int j = 0; j <= 50; j++) {
            if (freq[j] == 0) continue;
            if (rem[i][j] == 0) continue;
            if (rem[i][j] == freq[j]) num++;
        }

        best = min(best, num);
    }

    cout << max(tot - best, 0) << endl;

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