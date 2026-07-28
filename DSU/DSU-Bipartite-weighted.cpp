#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define ll long long
#define sp " "

const int N = 100005;

struct WeightedDSU {
    int par[N];
    long long w[N]; // w[u] = value[u] - value[parent_of_u]

    void init(int n) {
        fill(par, par + n, -1);
        fill(w, w + n, 0);
    }

    // Returns {root, value[u] - value[root]}
    pair<int, long long> find(int u) {
        if (par[u] < 0) return {u, 0};
        auto [root, wr] = find(par[u]);
        w[u] += wr; // path compression: accumulate weight
        par[u] = root;
        return {root, w[u]};
    }

    // Constraint: value[v] - value[u] = d
    // Returns false if it contradicts existing information
    bool join(int u, int v, long long d) {
        auto [ru, wu] = find(u); // wu = value[u] - value[ru]
        auto [rv, wv] = find(v); // wv = value[v] - value[rv]
        
        if (ru == rv) {
            return (wv - wu) == d; // check consistency: value[v]-value[u] = wv-wu
        }

        // --- UNION BY SIZE (The "Missing If") ---
        // Ensure ru is the root of the larger component
        if (par[ru] > par[rv]) {
            swap(ru, rv);
            swap(wu, wv);
            d = -d; // Because constraint was v-u=d, swapping makes it u-v=-d
        }
        par[ru] += par[rv];
        // ----------------------------------------

        par[rv] = ru;
        w[rv] = wu - wv + d; // so that value[v]-value[u] = d holds
        return true;
    }

    // Query: value[v] - value[u] (must be in same component)
    long long query(int u, int v) {
        auto [ru, wu] = find(u);
        auto [rv, wv] = find(v);
        if (ru != rv) return LLONG_MIN; // Use a flag for "not connected"
        return wv - wu;
    }
};

int main() {

    WeightedDSU wdsu;
    wdsu.init(5);

    bool ok1 = wdsu.join(0, 1, 5); // value[1]-value[0] = 5
    cout << "join(0,1,5): " << ok1 << " (1=ok)" nl;

    bool ok2 = wdsu.join(1, 2, 3); // value[2]-value[1] = 3
    cout << "join(1,2,3): " << ok2 << " (1=ok)" nl;

    ll q1 = wdsu.query(0, 2); // expect 8
    cout << "query(0,2) = " << q1 << " (expected 8)" nl;

    bool ok3 = wdsu.join(0, 2, 8); // consistent with derived value
    cout << "join(0,2,8): " << ok3 << " (1=ok, consistent)" nl;

    bool ok4 = wdsu.join(0, 2, 100); // contradicts derived value
    cout << "join(0,2,100): " << ok4 << " (0=conflict)" nl;
}