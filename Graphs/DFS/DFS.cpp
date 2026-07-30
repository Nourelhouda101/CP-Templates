#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define sp " "
#define ll long long

vector<vector<int>> adj;
vector<bool> vis;
vector<int> color_arr, tin, tout, low;
vector<int> parent;
stack<int> topo_stack;
vector<pair<int,int>> bridges;
int timer_ = 0;

// directed = false builds an undirected graph (adds both x->y and y->x)
void graph_rep(int n, int m, bool directed = false) {
    adj.assign(n + 1, {});
    int x, y;
    for (int i = 1; i <= m; i++) {
        cin >> x >> y;
        adj[x].push_back(y);
        if (!directed) adj[y].push_back(x);
    }
}

// Plain reachability DFS
void dfs(int u) {
    vis[u] = 1;
    for (int v : adj[u]) {
        if (!vis[v])
            dfs(v);
    }
}

// Iterative version — use for large/skewed graphs to avoid stack overflow
void dfs_iterative(int start) {
    stack<int> st;
    st.push(start);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int v : adj[u]) {
            if (!vis[v]) st.push(v);
        }
    }
}

// DFS for a Tree (just parent and child relationship)
void dfs_tree(int u, int p) {
    parent[u] = p;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs_tree(v, u);
    }
}

// Component size (neighbors and neighbors of neighbors)
ll dfsCount(int u) {
    vis[u] = 1;
    ll cnt = 1;
    for (int v : adj[u]) {
        if (!vis[v])
            cnt += dfsCount(v);
    }
    return cnt;
}

// Cycle detection for DIRECTED graphs + topo sort (via topo_stack)
// Call for every unvisited node (color_arr[i] == 0), OR-ing the results.
bool dfs_cycle_directed(int u) {
    color_arr[u] = 1; // gray
    for (int v : adj[u]) {
        if (color_arr[v] == 0) {
            if (dfs_cycle_directed(v))
                return true;
        } else if (color_arr[v] == 1) {
            return true; // back edge = cycle
        }
    }
    color_arr[u] = 2; // black
    topo_stack.push(u);
    return false;
}

vector<int> get_topo_order() {
    vector<int> order;
    while (!topo_stack.empty()) {
        order.push_back(topo_stack.top());
        topo_stack.pop();
    }
    return order;
}

// Cycle detection for UNDIRECTED graphs
bool dfs_cycle_undirected(int u, int p) {
    vis[u] = 1;
    for (int v : adj[u]) {
        if (!vis[v]) {
            if (dfs_cycle_undirected(v, u))
                return true;
        } else if (v != p) {
            return true;
        }
    }
    return false;
}

// Bipartite check (2-coloring). Call with c = 1 on every uncolored node.
bool dfs_bipartite(int u, int c) {
    color_arr[u] = c;
    for (int v : adj[u]) {
        if (color_arr[v] == 0) {
            if (!dfs_bipartite(v, 3 - c))
                return false;
        } 
        else if (color_arr[v] == color_arr[u]) {
            return false;
        }
    }
    return true;
}

// Tree/DAG subtree depth (skip parent so it terminates on undirected graphs)
int dfsDepth(int u, int p) {
    int maxx = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        maxx = max(maxx, dfsDepth(v, u));
    }
    return maxx + 1;
}

// Entry/exit times — foundation for Euler Tour, LCA, subtree queries.
// v is a descendant of u  <=>  tin[u] <= tin[v] < tout[u]
void dfs_time(int u, int p) {
    tin[u] = timer_++;
    vis[u] = 1;
    for (int v : adj[u]) {
        if (v == p) 
        continue;

        if (!vis[v]) 
        dfs_time(v, u);
    }
    tout[u] = timer_++;
}

// Bridges (and articulation point groundwork) via low-link.
// Pushes every bridge edge into the global `bridges` vector.
void dfs_bridges(int u, int p) {
    vis[u] = 1;
    tin[u] = low[u] = timer_++;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (vis[v]) {
            low[u] = min(low[u], tin[v]);
        } else {
            dfs_bridges(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) {
                bridges.push_back({u, v}); // edge (u, v) is a bridge
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; // nodes, edges
    cin >> n >> m;
    graph_rep(n, m); // pass true as 3rd arg if the graph is directed

    vis.assign(n + 1, false);
    color_arr.assign(n + 1, 0);
    tin.assign(n + 1, -1);
    tout.assign(n + 1, -1);
    low.assign(n + 1, -1);
    parent.assign(n + 1, -1);

    // ---- Connected components / reachability ----
    int components = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i);

            components++;
        }
    }
    cout << "Components: " << components << nl;

    // ---- Bipartite check (2-coloring), per component ----
    color_arr.assign(n + 1, 0);
    bool bipartite = true;
    for (int i = 1; i <= n; i++)
        if (color_arr[i] == 0 && !dfs_bipartite(i, 1)) 
            bipartite = false;

    cout << (bipartite ? "bipartite" : "not bipartite") << nl;

    // ---- Cycle detection + topo sort — DIRECTED graphs only ----
    // (rebuild with graph_rep(n, m, true) before this)
    color_arr.assign(n + 1, 0);
    bool has_cycle = false;
    for (int i = 1; i <= n; i++)
        if (color_arr[i] == 0 && dfs_cycle_directed(i)) 
          has_cycle = true;
        
    cout << (has_cycle ? "cycle" : "no cycle") << nl;
    if (!has_cycle) {
        for (int u : get_topo_order()) 
          cout << u << sp;

        cout << nl;
    }

    // ---- Cycle detection — UNDIRECTED graphs, per component ----
    vis.assign(n + 1, false);
    bool has_cycle_u = false;
    for (int i = 1; i <= n; i++)
        if (!vis[i] && dfs_cycle_undirected(i, 0)) 
           has_cycle_u = true;

    cout << (has_cycle_u ? "cycle" : "no cycle") << nl;

    // ---- Tree parent/depth (graph must be a tree, or run per-component) ----
    dfs_tree(1, 0);
    cout << "Depth from 1: " << dfsDepth(1, 0) << nl;

    // ---- Component size ----
    vis.assign(n + 1, false);
    cout << "Size of component containing 1: " << dfsCount(1) << nl;

    // ---- tin/tout (Euler tour), per component ----
    vis.assign(n + 1, false);
    timer_ = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i]) 
          dfs_time(i, 0);

    // ---- Bridges, per component ----
    vis.assign(n + 1, false);
    timer_ = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i]) 
          dfs_bridges(i, 0);
          
    for (auto& [u, v] : bridges)
    cout << u << sp << v << nl;

    return 0;
}