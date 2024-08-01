// #include <cstdio>

/*
 * Problem takeaways:
 *
 * there's some implementation trolling with this problem which is the only hard part really.
 *
 * My first approach I tried to dfs for each cell and when it reaches the lab we do something about that.
 * Somehow this didn't work but I'm not sure why.
 *
 * Obviously the cleaner approach is just to DFS starting from the lab, that way we don't have to deal with any
 * edge cases.
 *
 *
 *
 *
 */
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
// const int MOD = 1'000'000'000 + 7;
const int MOD2 = 998'244'353;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {-1, 1, 0, 0};

int n, m;

bool dfs(vector<vector<int>>& mat, vector<vector<bool>>& ans, vector<vector<bool>>& visited, int r, int c, int parent_r, int parent_c) {

    int count = 0;

    for (int i = 0; i < 4; i++) {
        int new_r = r + dy[i];
        int new_c = c + dx[i];

        if (new_r == parent_r && new_c == parent_c) continue;
        if (new_r < 0 || new_r >= n || new_c < 0 || new_c >= m) continue;

        if (mat[new_r][new_c] == 1) continue;
        if (ans[new_r][new_c]) continue;

        count++;
    }

    bool works = count <= 1 || mat[r][c] == 2 || ans[r][c];

    //  cout << r << " " << c << " "

    if (works) {
        for (int i = 0; i < 4; i++) {
            int new_r = r + dy[i];
            int new_c = c + dx[i];

            if (new_r == parent_r && new_c == parent_c) continue;
            if (new_r < 0 || new_r >= n || new_c < 0 || new_c >= m) continue;

            if (mat[new_r][new_c] == 1) continue;
            if (visited[new_r][new_c]) continue;

            visited[r][c] = true;
            dfs(mat, ans, visited, new_r, new_c, r, c);
            visited[r][c] = false;
        }
    }

    // cout << r << " " << c << " " << parent_r << " " << parent_c << " " << works << " " << wrong << endl;

    ans[r][c] = works;
    return ans[r][c];
}


void solve() {
    cin >> n >> m;

    int lab_r, lab_c;

    vector<vector<int>> mat(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        for (int j = 0; j < m; j++) {
            if (s[j] == '.') mat[i][j] = 0;
            else if (s[j] == '#') mat[i][j] = 1;
            else if (s[j] == 'L') {
                mat[i][j] = 2;
                lab_r = i;
                lab_c = j;
            }
        }
    }

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<vector<bool>> ans(n, vector<bool>(m, false));

    visited[lab_r][lab_c] = true;
    ans[lab_r][lab_c] = true;

    dfs(mat, ans, visited, lab_r, lab_c, -1, -1);

    for (int i = 0; i < n; i++) {
        string s;
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == 1) s += "#";
            else if (mat[i][j] == 2) s += "L";
            else {
                if (ans[i][j]) s += "+";
                else s += ".";
            }
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
