#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define sp " "

const int N = 100005;
struct DSU {
// par[u] < 0  -> root, component size = -par[u]
// par[u] >= 0 -> non-root, parent = par[u]
int par[N], ncmp, sets[N], pos[N];
int tail[N], nxt[N];
void init(int n) {
    memset(par, -1, n * sizeof par[0]); // -1 = root of size 1 (-(-1)=1)
    iota(sets, sets + n, 0);            // active root list: sets[0..ncmp-1]
    iota(pos, pos + n, 0);              // pos[u] = index of u in sets[]
    iota(tail, tail + n, 0);            // tail[u] = last node in u's linked list
    ncmp = n;
    memset(nxt, -1, n * sizeof nxt[0]);
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
    par[b] += par[s];                // merge sizes: both negative, sum = larger size
    par[s] = b;                      // s becomes child of b

    int &t = tail[b];
    nxt[t] = s; t = tail[s];

    int p = pos[s];
    sets[p] = sets[--ncmp];
    pos[sets[p]] = p;

    return true;
}

// Returns all nodes in the component containing u.
vector<int> getCmp(int u) {
    u = find(u);
    vector<int> ret;
    ret.reserve(-par[u]); // preallocate with component size
    for (int v = u; v != -1; v = nxt[v])
        ret.push_back(v);
    return ret;
}

// Returns all components as a list of node lists.
vector<vector<int>> getCmps() {
    vector<vector<int>> ret;
    ret.reserve(ncmp); // preallocate with number of components
    for (int i = 0; i < ncmp; i++)
        ret.push_back(getCmp(sets[i]));
    return ret;
}
};

int main() {
    int n, m;
    cin >> n >> m;

    DSU dsu;
    dsu.init(n); // 0-based

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        dsu.join(u, v);
    }

    // How many components remain after join
    cout << "Components: " << dsu.ncmp << nl;

    // Are node a and node b in the same component (have same root)?
    int a = 0, b = 1;
    if (dsu.find(a) == dsu.find(b))
        cout << a << " and " << b << " are in the same component" << nl;

    else
        cout << a << " and " << b << " are NOT in the same component" << nl;

    // Get the full member list of the component containing node 0
    vector<int> comp0 = dsu.getCmp(0);
    cout << "Component of 0 has " << comp0.size() << " nodes: ";
    for (int x : comp0) 
    cout << x << sp;

    cout << nl;

    // Get the elements of each component
    vector<vector<int>> all = dsu.getCmps();
    for (auto &c : all) {
        cout << "Component: ";

        for (int x : c) 
        cout << x << sp;

        cout << nl;
    }
}