
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

int n, m;
int mat[1005][1005];

int dr[4] = {0, 0, -1, 1};
int dc[4] = {1, -1, 0, 0};

char dir[4] = {'R', 'L', 'U', 'D'};

void solve() {
    cin >> n >> m;

    int sr, sc, er, ec;


    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        for (int j = 0; j < m; j++) {
            if (s[j] == '.') mat[i][j] = 0;
            else if (s[j] == 'A') {sr = i; sc = j;}
            else if (s[j] == 'B') {er = i; ec = j;}
            else mat[i][j] = 1;
        }
    }

    queue<pii> q;

    q.push({sr, sc});

    int parents[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) parents[i][j] = -1;
    }

    bool works = false;

    while (!q.empty()) {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        if (row == er && col == ec) {
            works = true;
            break;
        }

        for (int d = 0; d < 4; d++) {
            int new_r = row + dr[d];
            int new_c = col + dc[d];

            if (new_r < 0 || new_r >= n || new_c < 0 || new_c >= m || mat[new_r][new_c] == 1) continue;
            if (parents[new_r][new_c] != -1) continue;

            parents[new_r][new_c] = d;
            q.push({new_r, new_c});
        }
    }

    if (!works) {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;

    pii curr = {er, ec};
    string s;

    while (true) {
        // cout << curr.first << " " << curr.second << " " << parents[curr.first][curr.second] << endl;

        int new_row = curr.first + -1 * dr[parents[curr.first][curr.second]];
        int new_col = curr.second + -1 * dc[parents[curr.first][curr.second]];

        char d = dir[parents[curr.first][curr.second]];
        s += d;

        curr = {new_row, new_col};

        if (new_row == sr && new_col == sc) break;
    }

    reverse(s.begin(), s.end());
    cout << s.size() << endl;
    cout << s << endl;


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

