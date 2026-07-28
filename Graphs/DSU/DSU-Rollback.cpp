#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define sp " "

const int N = 100005;
const int M = 100005;

struct DSU
{
// par[u] < 0  -> root, size = -par[u]
// par[u] >= 0 -> non-root, parent = par[u]
int par[N], curT, curTtoSs[M];
void init(int n)
{
    curT = 0;
    memset(par, -1, n * sizeof par[0]); // -1 = root of size 1
}

// Each op saves {node, its old par, other node or -1, its old par}
struct operation { int a, parA, b, parB; };
stack<operation> ops;

// Find operation with path compression (logged for rollback)
int operator[](int u)
{
    if(par[u] < 0) return u;          // root check
    ops.push({u, par[u], -1, 0});     // compression: only par[u] changes
    return par[u] = (*this)[par[u]];
}

// Join operation (union by size)
bool operator()(int a, int b)
{
    curTtoSs[curT++] = ops.size();
    a = (*this)[a];
    b = (*this)[b];
    if(a == b) return 0;
    if(par[a] > par[b]) swap(a, b);   // a has bigger size (more negative)
    ops.push({b, par[b], a, par[a]}); // save BOTH roots (both par values change)
    par[a] += par[b];                 // merge sizes (both negative -> sum more negative)
    par[b] = a;                       // b becomes child of a
    return 1;
}

void rollBack()
{
    auto &op = ops.top();
    par[op.a] = op.parA;
    if(~op.b) par[op.b] = op.parB;    // restore other root's par (size) if union op
    ops.pop();
}

void rollUntil(int t)
{
    while(ops.size() > curTtoSs[t + 1])
        rollBack();
    curT = t + 1;
}
} dsu;

int main() {
    int n = 5;
    dsu.init(n); // 0-based

    dsu(0, 1);
    dsu(1, 2);
    dsu(3, 4);

    // Roll back to the state right after call 0 (undoes calls 1 and 2)
    dsu.rollUntil(0);
    cout << "After rollUntil(0):" nl;
    cout << "  0 and 1 connected? " << (dsu[0] == dsu[1] ? "yes" : "no") << nl;
    cout << "  0 and 2 connected? " << (dsu[0] == dsu[2] ? "yes" : "no") << nl;
    cout << "  3 and 4 connected? " << (dsu[3] == dsu[4] ? "yes" : "no") << nl;
}