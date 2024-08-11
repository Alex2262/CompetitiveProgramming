
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

// ~9 * 10 ^ 18
const ll LL_MAX = 9'223'372'036'854'775'807;

// ~2 * 10 ^ 9
const int MAX = 2'147'483'647;
const int MOD = 1'000'000'000 + 7;
const int MOD2 = 998'244'353;

// MATH, NUMBER THEORY

namespace Math {
    int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, (a % b));
    }

    // PRIME NUMBER ALGORITHMS

    // Sieve of Eratosthenes
    // O(n log log n)
    vector<bool> sieve(int n) {
        vector<bool> prime;
        prime.resize(n + 1);

        prime[0] = false;
        prime[1] = false;

        std::fill(prime.begin(), prime.end(), true);

        // We only need to loop up to sqrt(n) since all composite (non-prime) numbers larger than sqrt(n)
        // obviously have a factor <= sqrt(n). All factors less than sqrt(n) will be solved for,
        // and their multiples will be marked.
        for (int p = 2; p * p <= n; p++) {
            if (!prime[p]) continue;

            // If this number is prime, we must mark all multiples as non-prime.
            // We can start from p * p because obviously all p * x s.t. x < p will have been marked already
            for (int i = p * p; i <= n; i += p) prime[i] = false;
        }

        return prime;
    }

    vector<int> sieve_factors(int n) {
        vector<int> prime_factor;
        prime_factor.resize(n + 1);

        prime_factor[0] = 1;  // we should not use this...
        prime_factor[1] = 1;

        for (int i = 2; i < n; i++) {
            if (i & 1) prime_factor[i] = i;
            else prime_factor[i] = 2;
        }

        for (int p = 3; p * p <= n; p++) {
            if (prime_factor[p] != p) continue;

            for (int i = p * p; i <= n; i += p) prime_factor[i] = p;
        }

        return prime_factor;
    }

    // Construct a table with each value being the largest prime <= the index of the element
    void fill_table(int n) {
        vector<bool> prime_table;
        vector<bool> prime = sieve(n);

        prime_table.resize(n + 1);
        std::fill(prime_table.begin(), prime_table.end(), 1);

        int last_prime = 2;
        for (int i = 2; i <= n; i++) {
            if (prime[i]) last_prime = i;

            prime_table[i] = last_prime;
        }
    }

    void prime_factors(map<int, int>& m, int n) {
        while (n % 2 == 0) {
            m[2]++;
            n = n / 2;
        }

        for (int i = 3; i <= sqrt(n); i = i + 2) {
            while (n % i == 0) {
                m[i]++;
                n = n / i;
            }
        }

        if (n > 2) m[n]++;
    }

    void prime_factors_sieve(vector<int>& prime_factor, map<int, int>& m, int n) {
        if (n <= 1) return;

        while (n > 1) {
            m[prime_factor[n]]++;
            n /= prime_factor[n];
        }
    }

    void prime_factors_unique(map<int, int>& m, int n) {
        set<int> primes;
        while (n % 2 == 0) {
            primes.insert(2);
            n = n/2;
        }

        for (int i = 3; i <= sqrt(n); i = i + 2) {
            while (n % i == 0) {
                primes.insert(i);
                n = n/i;
            }
        }

        if (n > 2)
            primes.insert(n);

        for (auto& e : primes) {
            m[e]++;
        }
    }

    ll bin_exp(ll x, ll y) {
        ll res = 1;
        x = x % MOD;
        while (y > 0) {
            if (y & 1) res = (res * x) % MOD;
            y = y >> 1;
            x = (x * x) % MOD;
        }
        return res;
    }

    ll mod_inverse(ll n) {
        return bin_exp(n, MOD - 2);
    }

    // nCr
    ll binomial(vector<ll>& fac, ll n, ll r) {
        if (r == 0) return 1;
        return (fac[n] * mod_inverse(fac[r]) % MOD * mod_inverse(fac[n - r]) % MOD) % MOD;
    }
}

// Binary Search
namespace BinSearch {
    // lower bound
    int lower_bound(vector<int>& a, int n, int x) {
        int l = 0;
        int r = n;

        while (l < r) {
            int mid = l + (r - l) / 2;

            if (a[mid] >= x) r = mid;
            else l = mid + 1;
        }

        return l;
    }
}


// GRAPHS

namespace Graphs {
    // Depth First Search (DFS)
    void dfs(vector<vector<int>>& g, int node, int parent) {
        // actions

        for (int child : g[node]) {
            if (child == parent) continue;

            dfs(g, child, node);
        }
    }

// Breadth First Search (BFS)
    void bfs() {
        int n;
        vector<vector<int>> g;

        vector<bool> visited(n, false);
        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            visited[node] = true;

            // actions

            for (int child : g[node]) {
                if (visited[child]) continue;
                q.push(child);
            }
        }
    }


/*
 * Topological Sort
 *
 * Scheduling problems
 * Cycle Finding
 *
 * Uses Kahn's algorithm
 * Time Complexity: O(V+E)
 */
    vector<int> topological_sort(vector<vector<int>>& g) {

        int n = g.size();

        vector<int> in_degree(n, 0);

        for (int i = 0; i < n; i++) {
            for (int child : g[i]) {
                in_degree[child]++;
            }
        }


        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }

        int visited = 0;
        vector<int> sorted;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            sorted.push_back(node);

            for (int child : g[node]) {
                in_degree[child]--;
                if (in_degree[child] == 0) {
                    q.push(child);
                }
            }

            visited++;
        }

        if (visited != n) {
            /*
             * A cycle is present
             * All nodes added inside the sorted vector should not be in a cycle since they had 0 in-degree
             * Nodes not added may be in a cycle
             */
            return {};
        }

        return sorted;
    }
}


/*
 * Disjoint Set Union (DSU)
 *
 * Time Complexity:
 * make_set: O(1)
 * find_set: O(log(n))
 * union_sets: O(1)
 */

namespace DSU {
    vector<int> parent;

    void make_set(int v) {
        parent[v] = v;
    }

    int find_set(int v) {
        if (v == parent[v]) return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b)
            parent[b] = a;
    }
}

// Merge Sort
// Counting inversions

namespace MergeSort {

    int merge_count(vector<int>& a, int l, int r, int mid) {
        int i = l;   // index for left subarray
        int j = mid + 1; // index for right subarray
        int k = 0;   // index for temp array
        int inversion_count = 0;

        vector<int> temp(r - l + 1); // We use this for performing the merge

        // We choose which element to put next into temp
        while (i <= mid && j <= r) {
            if (a[i] <= a[j]) {
                temp[k++] = a[i++];
            } else {
                temp[k++] = a[j++];
                inversion_count += (mid - i + 1);
            }
        }

        // Put the rest of the elements from the sub-arrays
        while (i <= mid) temp[k++] = a[i++];
        while (j <= r  ) temp[k++] = a[j++];

        for (i = l, k = 0; i <= r; i++, k++) {
            a[i++] = temp[k++];
        }

        return inversion_count;
    }

    int merge_sort_count(vector<int>& a, int l, int r) {
        if (l >= r) return 0;
        int inversion_count = 0;

        int mid = l + (r - l) / 2;
        inversion_count += merge_sort_count(a, l, mid);
        inversion_count += merge_sort_count(a, mid + 1, r);

        inversion_count += merge_count(a, l, r, mid);

        return inversion_count;
    }
}


/*
 * RANGE QUERIES
 *
 * Segtree
 * Fenwick Tree
 * Difference Arrays
 * SQRT Decomposition
 */


namespace Segtree {
    // https://codeforces.com/blog/entry/18051
    // Based on the binary tree
    // Our actual array is represented by the leaf nodes of the tree
    // So it is stored from indexes in the set of [n, 2 * n)

    // Notes:
    // tree[0] doesn't hold any value
    // tree[1] is the root

    // Max N value
    const int N = 5e5;
    int tree[N * 2];
    int n;

    // BUILD TREE
    // O(n)
    // Note that:
    // 1. i << 1     == i * 2
    // 2. i << 1 | 1 == i * 2 + 1
    void build() {
        for (int i = n - 1; i > 0; i--) tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }

    // MODIFY TREE (single point)
    // O(log(n))
    // Note that:
    // p ^ 1 ensures we add both child nodes
    void modify_point(int p, int value) {
        p += n;
        tree[p] = value;
        for (; p > 1; p >>= 1) tree[p >> 1] = tree[p] + tree[p ^ 1];
    }

    // MODIFY TREE (range)
    // O(log(n))
    // on range [l, r)
    void modify_range(int l, int r, int value) {
        l += n, r += n;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) tree[l++] += value;
            if (r & 1) tree[--r] += value;
        }
    }

    // QUERY (range)
    // O(log(n))
    // sum on interval [l, r)
    int query_range(int l, int r) {
        l += n, r += n;
        int res = 0;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += tree[l++];
            if (r & 1) res += tree[--r]; // Remember that r is the excluded bound
        }

        return res;
    }

    // QUERY POINT
    // O(log(n))
    // If we ever use this we cannot build the tree!!!!!
    // We only store the updates in the segtree.
    int query_point(int p) {
        p += n;
        int res = 0;
        for (; p > 0; p >>= 1) res += tree[p];
        return res;
    }

    // PUSH
    void push() {
        for (int i = 1; i < n; i++) {
            tree[i << 1] += tree[i];
            tree[(i << 1) | 1] += tree[i];
            tree[i] = 0;
        }
    }

}


namespace DifferenceArray {
    // https://codeforces.com/blog/entry/78762

}



namespace SqrtDecomp {
    // https://cp-algorithms.com/data_structures/sqrt_decomposition.html
    // Divide blocks into sqrt(n) size
    // Works on range queries, point queries, range updates, point updates
    //


    void range_minimum_query(vector<ll>& a, int n, int q) {
        // Each block will store like [0, sqrt(n))
        int block_size = static_cast<int>(sqrt(n)) + 1;
        vector<ll> blocks(block_size, LL_MAX);

        for (int i = 0; i < n; i++) {
            blocks[i / block_size] = min(blocks[i / block_size], a[i]);
        }

        vector<ll> ans;
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            l--, r--;

            // Check the current blocks that l and r correspond to
            int c_l = l / block_size, c_r = r / block_size;

            ll curr = LL_MAX;

            // Range is contained in the same block
            if (c_l == c_r) {
                for (int j = l; j <= r; j++) curr = min(curr, a[j]);
            }

            else {
                for (int j = l; j < (c_l + 1) * block_size; j++) curr = min(curr, a[j]);
                for (int j = c_l + 1; j < c_r; j++) curr = min(curr, blocks[j]);
                for (int j = c_r * block_size; j <= r; j++) curr = min(curr, a[j]);
            }

            ans.push_back(curr);
        }
    }
}


namespace LIS {

    // calculate longest non decreasing subsequence
    // (increasing and equal)
    void LNDS(vector<int>& a, vector<int>& lengths, int n) {
        vector<int> dp(n + 1, 0);
        int curr_max = 0;

        for (int i = 0; i < n; i++) {
            int ind = upper_bound(dp.begin(), dp.begin() + curr_max + 1, a[i]) - dp.begin();

            dp[ind] = a[i];
            lengths[i] = ind;

            curr_max = max(curr_max, ind);
        }
    }

    // longest increasing subsequence
    // (strictly increasing)
    void LIS(vector<int>& a, vector<int>& lengths, int n) {
        vector<int> dp(n + 1, 0);
        int curr_max = 0;

        for (int i = 0; i < n; i++) {
            int ind = lower_bound(dp.begin(), dp.begin() + curr_max + 1, a[i]) - dp.begin();

            dp[ind] = a[i];
            lengths[i] = ind;

            curr_max = max(curr_max, ind);
        }
    }
}