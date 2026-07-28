#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define sp " "

const int N = 100005;
struct DSU {
// par[u] < 0  ->  root, component size = -par[u]
// par[u] >= 0 ->  non-root, parent = par[u]
int par[N], ncmp;
void init(int n) {
    memset(par, -1, n * sizeof par[0]); // -1 = root of size 1
    ncmp = n;
}

int find(int u) {
    return par[u] < 0 ? u : par[u] = find(par[u]); // path compression
}

// s = small, b = big (by convention - swap if inconsistent).
// Returns false if s and b are already in the same component.
bool join(int s, int b) {
    s = find(s); b = find(b);
    if (s == b) return false;
    if (par[b] > par[s]) swap(s, b); // par more negative = bigger; ensure b is bigger
    par[b] += par[s];                // merge sizes (both negative -> sum more negative)
    par[s] = b;                      // s becomes child of b
    ncmp--;
    return true;
}
};

int main() {
    int n, m;
    cin >> n >> m;

    DSU dsu;
    dsu.init(n); // based 0

    int u, v;
    for(int i = 0; i < m; i++) {
        cin >> u >> v;
        dsu.join(u, v);
    }

    // How many connected components remain?
    cout << "Components: " << dsu.ncmp << nl;

    // Check if two specific nodes are connected
    int a = 0, b = 1;
    if (dsu.find(a) == dsu.find(b))
        cout << a << " and " << b << " are in the same component" << nl;
    else
        cout << a << " and " << b << " are in different components" << nl;

    // Get the size of the component containing a given node q
    int q = 0;
    int root = dsu.find(q);
    int size = -dsu.par[root];
    cout << "Component of " << q << " has size " << size << nl;
}