#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define sp " "

const int N = 100005;

struct ParityDSU {
int par[N], dist[N]; // dist[u] = XOR parity to root
void init(int n){
    fill(par, par+n, -1);
    fill(dist, dist+n, 0);
}

// Returns {root, distance_to_root}
pair<int,int> find(int u){
    if(par[u] < 0) return {u, 0}; // par[u]<0 means u is root
    auto [root, d] = find(par[u]);
    dist[u] ^= dist[par[u]]; // path compression + parity
    par[u] = root;
    return {root, dist[u]};
}

// p=0: u and v same group, p=1: different group
// Returns: -1=conflict, 0=new edge ok, 1=redundant ok
int addEdge(int u, int v, int p){
        auto [ru, du] = find(u);
        auto [rv, dv] = find(v);
        if(ru == rv){
            return (du ^ dv) == p ? 1 : -1; // check consistency
        }

        // --- ADDED UNION BY SIZE LOGIC ---
        // par[root] is negative; the more negative it is, the larger the component.
        // If par[ru] > par[rv], then ru is actually the smaller component.
        if (par[ru] > par[rv]) {
            swap(ru, rv);
            swap(du, dv);
        }
        par[ru] += par[rv]; // Merge the size of rv into ru
        // ----------------------------------

        par[rv] = ru; // rv (smaller) becomes child of ru (bigger)
        dist[rv] = du ^ dv ^ p; // set parity so dist[v] remains correct
        return 0;
    }
};

int main() {
    ParityDSU pdsu;
    pdsu.init(5);

    int r1 = pdsu.addEdge(0, 1, 1); // 0 and 1 differ
    cout << "addEdge(0,1,differ): " << r1 << " (0=new edge)" nl;

    int r2 = pdsu.addEdge(1, 2, 1); // 1 and 2 differ -> implies 0,2 same
    cout << "addEdge(1,2,differ): " << r2 << " (0=new edge)" nl;

    int r3 = pdsu.addEdge(0, 2, 0); // check: 0 and 2 same group -> should be consistent
    cout << "addEdge(0,2,same): " << r3 << " (1=redundant, consistent)" nl;

    int r4 = pdsu.addEdge(0, 2, 1); // conflicting claim: 0 and 2 differ
    cout << "addEdge(0,2,differ): " << r4 << " (-1=conflict)" nl;
}