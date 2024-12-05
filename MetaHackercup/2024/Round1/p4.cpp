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

void solve() {
    string s;
    cin >> s;

    int n = s.size();

    ll k;
    cin >> k;

    ll pos = 1;
    int start_i = n;

    vector<ll> ap(n + 1, 1);
    vector<ll> one_pos(n);
    vector<ll> two_pos(n);

    bool edge = false;

    if (k > 1) {
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '?') {
                if (i == n - 1) {
                    if (i > 0) {
                        if (s[i - 1] == '?') {
                            pos *= 15;
                            edge = true;
                        }

                        else {
                            int prev = s[i - 1] - '0';

                            // 0_ or 1_
                            if (prev <= 1) {
                                pos *= 9;
                            }

                                // 2_
                            else {
                                pos *= 6;
                            }
                        }
                    }

                        // _
                    else {
                        pos *= 9;
                    }
                }

                else {
                    if (!edge || i < n - 2) {
                        if (s[i + 1] == '?') {
                            pos *= 2;
                        } else {
                            int nn = s[i + 1] - '0';
                            // _7
                            if (nn > 6) {
                                s[i] = '1';
                            }

                                // _6
                            else {
                                pos *= 2;
                            }
                        }
                    }
                }
            }

            ap[i] = pos;

            if (pos >= k) {
                start_i = i;
                break;
            }
        }
    }


    for (int i = 0; i < start_i; i++) {
        if (s[i] != '?') continue;
        if (i < n - 1) {
            if (i == n - 2 && edge) {
                if (k <= 6) {
                    s[i] = '2';
                    ap[i + 1] = 6;
                } else {
                    s[i] = '1';
                    ap[i + 1] = 9;
                    k -= 6;
                }
            } else {
                if (s[i + 1] == '?') {
                    s[i] = '2';
                } else {
                    int nn = s[i + 1] - '0';
                    // _7
                    if (nn > 6) {
                        s[i] = '1';
                    }

                        // _6
                    else {
                        s[i] = '2';
                    }
                }
            }
        }

        else {
            if (i > 0) {
                if (s[i - 1] == '?') {
                    s[i] = '6';
                }

                else {
                    int prev = s[i - 1] - '0';

                    // 0_ or 1_
                    if (prev <= 1) {
                        s[i] = '9';
                    }

                        // 2_
                    else {
                        s[i] = '6';
                    }
                }
            }

                // _
            else {
                s[i] = '9';
            }
        }
    }

    for (int i = start_i; i < n; i++) {
        if (s[i] != '?') continue;

        if (i == n - 1) {
            // cout << "WHAT " << k << " " << ap[i] << endl;
            s[i] = char((ap[i] - k) + '1');
            continue;
        }

        if ((i == n - 2) && edge) {
            if (k <= 6) {
                s[i] = '2';
                ap[i + 1] = 6;
            } else {
                s[i] = '1';
                ap[i + 1] = 9;
                k -= 6;
            }
        }

        if (k > ap[i + 1]) {
            s[i] = '1';
            k -= ap[i + 1];
        }

        else {
            s[i] = '2';
        }
    }


    vector<ll> dp(n + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            dp[i + 1] = dp[0];
            continue;
        }

        int num = (s[i] - '0') + (s[i - 1] - '0') * 10;
        if (s[i - 1] != '0' && num >= 1 && num <= 26) {
            dp[i + 1] = (dp[i + 1] + dp[i - 1]) % MOD2;
        }

        if (s[i] != '0') {
            dp[i + 1] = (dp[i + 1] + dp[i]) % MOD2;
        }
    }

    cout << s << " " << dp[n] << endl;
}

void multi_solve() {
    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
}

int main() {

    freopen("/Users/alexandertian/CLionProjects/CompetitiveProgramming/MetaHackercup/2024/Round1/p4.in", "r", stdin);
    freopen("/Users/alexandertian/CLionProjects/CompetitiveProgramming/MetaHackercup/2024/Round1/p4.out", "w", stdout);

    /*
     * FAST IO
     * Remember to remove for interactive problems!!!
     * https://stackoverflow.com/questions/31162367/significance-of-ios-basesync-with-stdiofalse-cin-tienull
     */

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    multi_solve();
}


