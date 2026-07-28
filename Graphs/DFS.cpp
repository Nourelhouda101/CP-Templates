#include <bits/stdc++.h>
using namespace std;
 
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
 
template <typename T>
using ordered_set = tree<T, null_type, less<T>,
                         rb_tree_tag, tree_order_statistics_node_update>;
 
template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>,
                              rb_tree_tag, tree_order_statistics_node_update>;
 
#define nl "\n"
#define ll long long
#define sp " "
#define pi 3.141592654
#define all(v) v.begin(), v.end()
#define fixed(n) fixed << setprecision(n)
 
void files() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
    #endif
}

// Graph DFS Struct
struct GraphDFS {
    int n;
    vector<vector<int>> adj;
    vector<char> vis;
    vector<int> color;
    stack<int>s;

    // Initialize/Reset the graph for a new test case
    void init(int nodes) {
        n = nodes;
        adj.assign(n + 1, vector<int>());
        vis.assign(n + 1, 0);
        color.assign(n + 1, 0);
    }

    // Add edges (Pass true for directed, false for undirected)
    void add_edge(int u, int v, bool directed = false) {
        adj[u].push_back(v);

        if (!directed) {
            adj[v].push_back(u);
        }
    }

    // Normal DFS
    void dfs(int u) {
        vis[u] = 1;
        for (int v : adj[u]) {
            if (!vis[v]) 
            dfs(v);
        }
    }

    // DFS for a Tree (just parent and child relationship)
    void dfs_tree(int u, int p) {
        for (int v : adj[u]) {
            if (v == p) continue;
            dfs_tree(v, u);
        }
    }
    // Count components (neighbors and neighbors of neighbors)
    ll dfsCount(int u) {
        vis[u] = 1;
        ll cnt = 1;
        for (int v : adj[u]) {
            if (!vis[v]) {
                cnt += dfsCount(v);
            }
        }
        return cnt;
    }

    // Cycle detection for DIRECTED graphs (0=White, 1=Gray, 2=Black)
    // Topo sort if written with a stack.
    bool dfs_cycle_directed(int u) {
        color[u] = 1; // GRAY (currently visiting)
        for (int v : adj[u]) {
            if (color[v] == 0) { // not visited
                if (dfs_cycle_directed(v)) 
                return true;

            } else if (color[v] == 1) { // cycle
                return true; // Back edge found
            }
        }
        color[u] = 2; // BLACK (finished)
        s.push(u);
        return false;
    }

    // Cycle detection for UNDIRECTED graphs
    bool dfs_cycle_undirected(int u, int p) {
        vis[u] = 1;
        for (int v : adj[u]) {
            if (!vis[v]) {
                if (dfs_cycle_undirected(v, u)) return true;
            } else if (v != p) {
                return true; // Visited neighbor that is not the parent
            }
        }
        return false;
    }

    // Bipartite Check (2-coloring)
    bool dfs_bipartite(int u, int c) {
        color[u] = c;
        for (int v : adj[u]) {
            if (color[v] == 0) {
                if (dfs_bipartite(v, 3 - c)) return true;
            } else if (color[v] == color[u]) {
                return true; // Not bipartite (same color adjacent)
            }
        }
        return false;
    }

    // Tree/DAG Depth
    int dfsDepth(int u) {
        int maxx = 0;
        for (auto v : adj[u]) {
            maxx = max(maxx, dfsDepth(v));
        }
        return maxx + 1;
    }
};


// Grid DFS Struct (For 2D Matrices)
struct GridDFS {
    int rows, cols;
    vector<string> grid;
    vector<vector<bool>> vis;
    
    // Directions: Up, Down, Left, Right
    int di[4] = {-1, 1, 0, 0};
    int dj[4] = {0, 0, -1, 1};

    void init(int r, int c, const vector<string>& g) {
        rows = r;
        cols = c;
        grid = g;
        vis.assign(rows, vector<bool>(cols, false));
    }

    bool is_valid(int r, int c) {
        return r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] == '.' && !vis[r][c];
    }

    void dfs(int r, int c) {
        vis[r][c] = true;
        for (int k = 0; k < 4; k++) {
            int nr = r + di[k];
            int nc = c + dj[k];
            if (is_valid(nr, nc)) dfs(nr, nc);
        }
    }
};

template <int N, int M>
struct ForwardStar {
    //In case of weighted graph, put back all removed w.
    int head[N];
    int to[M];
    int nxt[M];
    //int wt[M];
    int ne;
 
    void init(int n) {
        ne = 0;
        fill(head, head + n + 1, -1); 
    }
 
    // Removed the 'int w' parameter
    void addEdge(int u, int v) {
        to[ne] = v;
        //wt[ne] = w;
        nxt[ne] = head[u];
        head[u] = ne++;
    }
 
    // Removed the 'int w' parameter
    void addBiEdge(int u, int v) {
        addEdge(u, v);
        addEdge(v, u);
    }
 
    void traverse(int u) {
        cout << "Neighbors of node " << u << ": ";
 
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            //int w = wt[e];
            cout << v << sp;
        }
        cout << nl;
    }
};

void solve() {
    ll n,m;
    cin >> n >> m;

    GraphDFS dfs;
    GridDFS grid;

    dfs.init(n);
}
 
int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
    files();
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
 
        if (t != 0)
        cout << nl;
    }
 
    return 0;
}