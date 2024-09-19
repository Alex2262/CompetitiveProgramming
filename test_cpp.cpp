#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int l, n, m;
        cin >> l >> n >> m;
        vector<int> a(l);
        for(auto &x: a) cin >> x;
        vector<vector<int>> b(n, vector<int>(m));
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) cin >> b[i][j];
        }

        vector<vector<pair<int, int>>> list_v(8, vector<pair<int, int>>());
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                if(b[i][j] >=1 && b[i][j] <=7){
                    list_v[b[i][j]].emplace_back(i+1, j+1);
                }
            }
        }

        vector<vector<pair<int, int>>> list(l+1, vector<pair<int, int>>());
        for(int i=1;i<=l;i++) {
            if(a[i-1] >=1 && a[i-1] <=7){
                list[i] = list_v[a[i-1]];
            }
        }
        int size = n * m;
        vector<char> dp_next(size, 0);
        for(int i=l;i>=1;i--){
            vector<char> reachable(size, 0);
            for(auto &[x, y] : list[i]){
                if(x+1 > n || y+1 > m){
                    int idx = (x-1)*m + (y-1);
                    reachable[idx] = 1;
                }
                else{
                    if(x < n && y < m){
                        int next_idx = x * m + y;
                        if(dp_next[next_idx] == 0){
                            int idx = (x-1)*m + (y-1);
                            reachable[idx] = 1;
                        }
                    }
                    else{
                        int idx = (x-1)*m + (y-1);
                        reachable[idx] = 1;
                    }
                }
            }
            vector<char> suff_or(size, 0);
            for(int r=n;r>=1;r--){
                for(int c=m;c>=1;c--){
                    int idx = (r-1)*m + (c-1);
                    suff_or[idx] = reachable[idx];
                    if(r < n){
                        suff_or[idx] = suff_or[idx] || suff_or[idx + m];
                    }
                    if(c < m){
                        suff_or[idx] = suff_or[idx] || suff_or[idx + 1];
                    }
                }
            }
            dp_next = suff_or;
        }
        if(dp_next[0]) cout << "T\n";
        else cout << "N\n";
    }
}