#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define ll long long
#define sp " "

vector<vector<int>> adj;
vector<int> dist_arr, parent_arr, color_arr; // color_arr used only for bipartite check

void graph_rep(int n, int m) {
    adj.assign(n + 1, {});
    int x, y;
    for (int i = 1; i <= m; i++) {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x); // iff undirected graph
    }
}

bool BFS(int start_node, int n) {
    dist_arr.assign(n + 1, -1); //-1 --> not visited before, stores the shortest path(number of steps) for each node
    parent_arr.assign(n + 1, -1);
    color_arr.assign(n + 1, -1);

    queue<int> bfs;
    bfs.push(start_node);
    dist_arr[start_node] = 0;
    color_arr[start_node] = 0; // does every edge goes between two different groups?

    bool is_bipartite = true;

    while (!bfs.empty()) {
        int u = bfs.front();
        bfs.pop();
        // cout << u << sp; // if you want to print bfs order(order of visit)

        for (int v : adj[u]) {
            if (dist_arr[v] == -1) {
                dist_arr[v] = dist_arr[u] + 1;
                parent_arr[v] = u;
                color_arr[v] = 1 - color_arr[u]; //flip: 1 - 0 = 1, 1 - 1 = 0
                bfs.push(v);
            } else if (color_arr[v] == color_arr[u]) { // an edge connecting two nodes in the same group (not bipartite)
                is_bipartite = false; // ignore this if you don't need the check
            }
        }
    }
    return is_bipartite;
}

// path to lead to target node
vector<int> reconstruct_path(int target) {
    vector<int> path;

    if (dist_arr[target] == -1) 
    return path; // unreachable

    for (int v = target; v != -1; v = parent_arr[v])
    path.push_back(v);

    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int n, m;
    cin >> n >> m; // n = nodes, m = edges
    graph_rep(n, m);

    int start, target;
    cin >> start >> target;

    bool bipartite = BFS(start, n);

    // 1. shortest distance from start to target
    if (dist_arr[target] == -1)
        cout << "unreachable" << nl;
    else
        cout << "distance: " << dist_arr[target] << nl;

    // 2. actual shortest path (nodes in order)
    vector<int> path = reconstruct_path(target);
    if (!path.empty()) {
        cout << "path: ";
        for (int v : path) cout << v << sp;
        cout << nl;
    }

    // 3. bipartite check (only meaningful if you looped BFS over all components,
    cout << "bipartite: " << (bipartite ? "yes" : "no") << nl;
}