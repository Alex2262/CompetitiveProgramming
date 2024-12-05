
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
#include <numeric>
#include <functional>
#include <random>
#include <chrono>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define popcount    __builtin_popcount
#define popcount_ll __builtin_popcountll
#define lsb         __builtin_ctz
#define lsb_ll      __builtin_ctzll
#define msb(x)         (31 - __builtin_clz(x))   // change to 32 for uint
#define msb_ll(x)      (63 - __builtin_clzll(x)) // change to 64 for ull
#define parity      __builtin_parity

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

// PBDS
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// ~9 * 10 ^ 18
const ll LL_MAX = 9'223'372'036'854'775'807;

// ~2 * 10 ^ 9
const int MAX = 2'147'483'647;
const int MOD = 1'000'000'000 + 7;
const int MOD2 = 998'244'353;

// MATH, NUMBER THEORY

namespace Math {
    ll gcd(ll a, ll b) {
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

    // O(n log log n)
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

    // O (n sqrt n)
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

    // O(n log n)
    // requires filling table with sieve_factors
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

    ll binpow(ll x, ll y) {
        x %= MOD;

        ll res = 1;
        while (y > 0) {
            if (y & 1) res = (res * x) % MOD;
            x = (x * x) % MOD;
            y = y >> 1;
        }

        return res;
    }

    ll mod_inverse(ll n) {
        return binpow(n, MOD - 2);
    }

    // nCr
    ll binomial(vector<ll>& fac, vector<ll>& inv, ll n, ll r) {
        if (r == 0 || r > n) return 1;
        // return (fac[n] * mod_inverse(fac[r]) % MOD * mod_inverse(fac[n - r]) % MOD) % MOD;
        return (((fac[n] * inv[r]) % MOD) * inv[n - r]) % MOD;
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


// random stuff
namespace Hash {
    mt19937_64 rng(chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now().time_since_epoch()).count());
    uniform_int_distribution<ll> dist(1, LL_MAX);

    ull seed() {
        return dist(rng);
    }

    ull rand64(ull s) {
        s ^= s >> 12, s ^= s << 25, s ^= s >> 27;
        return s * 2685821657736338717LL;
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


    // O(V + E (log V))
    void dijkstra(vector<vector<pll>>& g, int n, int src) {
        priority_queue<pll, vector<pll>, greater<>> pq;

        ll dists[n];
        for (int i = 0; i < n; i++) dists[i] = LL_MAX;

        pq.push({0, src});
        dists[src] = 0;

        while (!pq.empty()) {
            auto p = pq.top();
            pq.pop();

            ll dist = p.first;
            ll node = p.second;

            if (dist > dists[node]) continue; // no longer optimal

            for (auto pc : g[node]) {
                ll child = pc.first;
                ll weight = pc.second;

                // if (dists[node] == LL_MAX) continue;

                ll new_dist = dists[node] + weight;
                if (new_dist < dists[child]) {
                    dists[child] = new_dist;
                    pq.push({dists[child], child});
                }
            }
        }
    }



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

    class DSU {

    private:
        vector<int> parents;
        vector<int> sizes;

    public:
        DSU(int size) : parents(size), sizes(size + 1, 1) {
            for (int i = 0; i < size; i++) parents[i] = i;
        }

        int find(int v) {
            if (v == parents[v]) return v;
            return parents[v] = find(parents[v]);
        }

        void unite(int a, int b) {
            a = find(a);
            b = find(b);
            if (a == b) return;

            if (sizes[a] < sizes[b]) swap(a, b);
            parents[b] = a;
            sizes[a] += sizes[b];
        }
    };
}


namespace BinLift {



    // int num_layers = __lg(n) + 1;
    // vector<vector<int>> bl_table(num_layers, vector<int>(n, -1));
    // fill_bl_table(bl_table, parents);


    void fill_bl_table(vector<vector<int>>& bl_table, vector<int>& parents) {

        int num_layers = bl_table.size();
        int n = bl_table[0].size();

        for (int i = 0; i < n; i++) bl_table[0][i] = parents[i];

        for (int layer = 1; layer < num_layers; layer++) {
            for (int i = 0; i < n; i++) {
                int p1 = bl_table[layer - 1][i];

                if (p1 == -1) {
                    bl_table[layer][i] = -1;
                    continue;
                }

                int p2 = bl_table[layer - 1][p1];
                bl_table[layer][i] = p2;
            }
        }
    }


    int kth_parent(vector<vector<int>>& bl_table, int node, int k) {
        int num_layers = bl_table.size();

        int res = node;
        for (int pow = 0; pow < num_layers; pow++) {
            if (k & (1 << pow)) {
                res = bl_table[pow][res];
                if (res == -1) break;
            }
        }

        return res;
    }


    int lca(vector<vector<int>>& bl_table, vector<int>& depth, int node1, int node2) {
        if (depth[node1] < depth[node2]) swap(node1, node2);

        // lift node1 up to the same level as node2
        node1 = kth_parent(bl_table, node1, depth[node1] - depth[node2]);
        if (node1 == node2) return node2;

        int num_layers = bl_table.size();
        for (int i = num_layers - 1; i >= 0; i--) {
            if (bl_table[i][node1] == bl_table[i][node2]) continue;

            node1 = bl_table[i][node1];
            node2 = bl_table[i][node2];
        }

        return bl_table[0][node1];
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


namespace Trie {
    const int K = 26;
    struct Vertex {
        int next[K];
        bool output = false;

        Vertex() {
            fill(begin(next), end(next), -1);
        }
    };

    vector<Vertex> trie(1);

    void add_string(string& s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (trie[v].next[c] == -1) {
                trie[v].next[c] = trie.size();
                trie.emplace_back();
            }

            v = trie[v].next[c];
        }

        trie[v].output = true;
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

    /*
     * BUILD TREE
     * O(n)
     * Note that:
     * 1. i << 1     == i * 2
     * 2. i << 1 | 1 == i * 2 + 1
     *
     * MODIFY TREE (single point)
     * O(log(n))
     * Note that:
     * p ^ 1 ensures we add both child nodes
     *
     * MODIFY TREE (range)
     * O(log(n))
     * on range [l, r)
     *
     * QUERY (range)
     * O(log(n))
     * sum on interval [l, r)
     *
     * QUERY POINT
     * O(log(n))
     *
     * If we ever use this we cannot build the tree!!!!!
     * We only store the updates in the segtree.
     */


    template <typename T> class Segtree {

    private:
        vector<T> tree;
        int size;

        T op(T a, T b) {
            return a + b;
        }

        T default_value = 0;  // TODO: CHANGE THIS FOR MIN/MAX

    public:
        Segtree(vector<T>& container) : tree(2 * container.size(), default_value) {
            size = container.size();
            for (int i = 0; i < size; i++) tree[i + size] = container[i];
            build();
        }

        void build() {
            for (int i = size - 1; i > 0; i--) tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
        }

        void modify_point(int p, T value) {
            p += size;
            tree[p] = value;
            for (; p > 1; p >>= 1) tree[p >> 1] = op(tree[p], tree[p ^ 1]);
        }

        T query_range(int l, int r) {
            l += size, r += size;
            T res = default_value;
            for (; l < r; l >>= 1, r >>= 1) {
                if (l & 1) res = op(res, tree[l++]);
                if (r & 1) res = op(res, tree[--r]);
            }

            return res;
        }

        void modify_range(int l, int r, T value) {
            l += size, r += size;
            for (; l < r; l >>= 1, r >>= 1) {
                if (l & 1) {
                    tree[l] = op(tree[l], value);
                    l++;
                }

                if (r & 1) {
                    r--;
                    tree[r] = op(tree[r], value);
                }
            }
        }

        T query_point(int p) {
            p += size;
            T res = default_value;
            for (; p > 0; p >>= 1) res = op(res, tree[p]);
            return res;
        }

        void push() {
            for (int i = 1; i < size; i++) {
                tree[i << 1] = op(tree[i << 1], tree[i]);
                tree[(i << 1) | 1] = op(tree[(i << 1) | 1], tree[i]);
                tree[i] = 0;
            }
        }
    };

}


namespace BIT {
    const int N = 2e5;
    int bit[N + 1];
    int sz;

    int query_sum(int p) {
        int res = 0;
        p++;

        while (p > 0) {
            res += bit[p];
            p -= p & (-p);
        }

        return res;
    }

    void modify_point(int p, int value) {
        p++;
        while (p <= sz) {
            bit[p] += value;
            p += p & (-p);
        }
    }

    void build(vector<int>& a) {
        for (int i = 0; i <= sz; i++) bit[i] = 0;
        for (int i = 0; i < sz; i++) modify_point(i + 1, a[i]);
    }

    /*
     * Find the K-th smallest element
     * Time  complexity: O(log^2 (mx)) time where mx is the maximum element
     * Space complexity: O(mx)
     * We can use this for mx <= 5 * 10^7 which is ~200 mb space
     *
     */

    void insert_element(int x) {
        modify_point(x, 1);
    }

    void delete_element(int x) {
        modify_point(x, -1);
    }

    int get_rank(int x) {
        return query_sum(x);
    }

    int kth_smallest(int k) {
        int l = 0;
        int r = sz - 1;
        int ans = 0;

        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (k <= query_sum(mid)) {
                ans = mid;
                r = mid - 1;
            } else l = mid + 1;
        }

        return ans;
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


namespace Mo {

    // Mo's Algorithm
    // Time complexity: O((N + Q) * F * sqrt(N)) where O(F) is the complexity of add and remove functions

    // maybe let block size be sqrt(Q/N) when ratio of Q to N is big?

    // notes:

    // In odd blocks, sort the right index in ascending order
    // In even blocks, sort the right index in descending order
    // This minimizes movement of the right pointer


    // https://codeforces.com/blog/entry/61203

    // https://cp-algorithms.com/data_structures/sqrt_decomposition.html

    void rem(int idx);  // TODO: remove value at idx from data structure
    void add(int idx);  // TODO: add value at idx from data structure
    int get();          // TODO: extract the current answer of the data structure

    const int BLOCK_SIZE = 700; // TODO: optimize

    struct Query {
        int l, r, idx;
    };

    bool cmp(Query& a, Query& b) {
        int a_block = a.l / BLOCK_SIZE;
        int b_block = b.l / BLOCK_SIZE;

        if (a_block != b_block) return a_block < b_block;

        if (a_block & 1) return a.r < b.r;
        return a.r > b.r;
    }

    vector<int> mo_algorithm(vector<Query> qs) {
        vector<int> ans(qs.size());

        sort(qs.begin(), qs.end(), cmp);

        // TODO: initialize data structure

        int curr_l = 0;
        int curr_r = -1;

        for (Query query : qs) {
            while (curr_l > query.l) add(--curr_l);
            while (curr_r < query.r) add(++curr_r);
            while (curr_l < query.l) rem(curr_l++);
            while (curr_r > query.r) rem(curr_r--);

            ans[query.idx] = get();
        }

        return ans;
    }

    // MO UPDATES OR MODIFICATION

    // https://codeforces.com/blog/entry/72690
    // O(S * Q + Q * N^2 / S^2)
    // Optimum block size S = (2n^2) ^ 1/3
    // Time complexity: O(Q * N^2/3)

    vector<int> mo_update(vector<Query> qs) {
        vector<int> ans(qs.size());

        sort(qs.begin(), qs.end(), cmp);

        // TODO: initialize data structure

        int curr_l = 0;
        int curr_r = -1;
        int curr_t = -1;

        for (Query query : qs) {
            while (curr_l > query.l) add(--curr_l);
            while (curr_r < query.r) add(++curr_r);
            while (curr_l < query.l) rem(curr_l++);
            while (curr_r > query.r) rem(curr_r--);

            ans[query.idx] = get();
        }

        return ans;
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


namespace Strings {

    void zfunc(vector<int>& z, string& s) {
        int n = s.size();
        z[0] = 0;

        // [l, r)
        int l = 0, r = 0;
        for (int i = 1; i < n; i++) {
            if (i < r) {
                z[i] = min(r - i, z[i - l]);
            }

            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                z[i]++;
            }

            if (i + z[i] > r) {
                l = i;
                r = i + z[i];
            }
        }
    }
}
