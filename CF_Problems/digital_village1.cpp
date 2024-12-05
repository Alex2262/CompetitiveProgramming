#pragma GCC optimize("O2,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

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
// const ll MOD = 1'000'000'000 + 7;
const ll MOD2 = 998'244'353;


/*
 *
 *
 *
 */


void floyd_warshall(vector<vector<ll>>& mat) {
    int n = mat.size();

    // Choose an intermediate vertex k
    for (int k = 0; k < n; k++) {

        // Pick a vertex to be the source vertex
        for (int i = 0; i < n; i++) {

            // Pick a vertex to be the destination vertex
            for (int j = 0; j < n; j++) {
                if (mat[i][k] == LL_MAX || mat[k][j] == LL_MAX) continue;

                ll new_dist = max(mat[i][k], mat[k][j]);
                if (new_dist < mat[i][j]) {
                    mat[i][j] = new_dist;
                }
            }
        }
    }
}

void solve() {
    int n, m, p;
    cin >> n >> m >> p;

    vector<int> s(p);
    for (int i = 0; i < p; i++) {
        cin >> s[i];
        s[i]--;
    }

    vector<vector<pll>> g(n);

    vector<vector<ll>> mat(n, vector<ll>(n, LL_MAX));

    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--, v--;

        g[u].push_back({v, w});
        g[v].push_back({u, w});

        mat[u][v] = w;
        mat[v][u] = w;
    }

    for (int i = 0; i < n; i++) {
        mat[i][i] = 0;
    }

    floyd_warshall(mat);


    vector<bool> used(n, false);
    vector<int> puse(p);

    string ans;

    ll tot = LL_MAX;
    int bi = -1;

    for (int i = 0; i < n; i++) {
        ll curr = 0;
        for (int j = 0; j < p; j++) {
            curr += mat[i][s[j]];
        }

        if (curr < tot) {
            tot = curr;
            bi = i;
        }
    }

    used[bi] = true;
    for (int j = 0; j < p; j++) {
        puse[j] = bi;
    }

    ans += to_string(tot);

    for (int k = 1; k < n; k++) {
        ll b = 0;
        bi = -1;

        for (int i = 0; i < n; i++) {
            if (used[i]) continue;

            ll curr = 0;
            for (int j = 0; j < p; j++) {
                if (mat[puse[j]][s[j]] > mat[i][s[j]]) {
                    curr += mat[puse[j]][s[j]] - mat[i][s[j]];
                }
            }

            if (curr > b) {
                b = curr;
                bi = i;
            }
        }

        if (bi != -1) {
            used[bi] = true;
            for (int j = 0; j < p; j++) {
                if (mat[puse[j]][s[j]] > mat[bi][s[j]]) {
                    puse[j] = bi;
                }
            }

            tot -= b;
        }

        ans += " " + to_string(tot);
    }

    cout << ans << endl;

}

void multi_solve() {
    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        solve();
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

    multi_solve();
}


