
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
#include <numeric>
#include <functional>

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

/*
 *
 *
 *
 *
 *
 */


// O(n^3)
void floyd_warshall(vector<vector<ll>>& mat) {
    int n = mat.size();

    // Choose an intermediate vertex k
    for (int k = 0; k < n; k++) {

        // Pick a vertex to be the source vertex
        for (int i = 0; i < n; i++) {

            // Pick a vertex to be the destination vertex
            for (int j = 0; j < n; j++) {
                if (mat[i][k] == LL_MAX || mat[k][j] == LL_MAX) continue;

                ll new_dist = mat[i][k] + mat[k][j];
                if (new_dist < mat[i][j]) {
                    mat[i][j] = new_dist;
                }
            }
        }
    }
}


void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<ll>> mat(n, vector<ll>(n, LL_MAX));

    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        a--, b--;

        mat[a][b] = min(mat[a][b], c);
        mat[b][a] = min(mat[b][a], c);
    }

    for (int i = 0; i < n; i++) {
        mat[i][i] = 0;
    }

    floyd_warshall(mat);

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;

        if (mat[a][b] == LL_MAX) cout << -1;
        else cout << mat[a][b];

        cout << endl;
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


    solve();

    /*
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    */
}

