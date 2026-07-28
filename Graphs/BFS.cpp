#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define sp " "

vector<vector<int>> adj; // holds the nodes and their adjacency

void graph_rep(int n, int m) {
    adj.resize(n + 1);
    int x, y;
    for (int i = 1; i <= m; i++) {
        cin >> x >> y; // node, the adjacent one
        adj[x].push_back(y);
        adj[y].push_back(x); // iff undirected graph
    }
}

void BFS(int start_node, int n) {
    vector<bool> vis(n + 1, 0);
    queue<int> bfs;
    bfs.push(start_node);
    vis[start_node] = 1;
    while (!bfs.empty()) {
        int parent = bfs.front();
        bfs.pop();
        cout << parent << sp;

        for (int i : adj[parent]) {
            if (vis[i] == 0) {
                vis[i] = 1;
                bfs.push(i);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m; // n = number of nodes, m = number of edges

    graph_rep(n, m);

    int start;
    cin >> start;

    cout << "BFS order: ";
    BFS(start, n);
    cout << nl;
}