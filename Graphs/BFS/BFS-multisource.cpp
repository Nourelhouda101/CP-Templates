#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define ll long long
#define sp " "

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
// use 8 directions if diagonal moves are allowed:
// int dx[] = {0,0,1,-1,1,1,-1,-1}, dy[] = {1,-1,0,0,1,-1,1,-1};

int rows, cols;
vector<string> grid;
vector<vector<int>> dist_grid;

void multiSourceBFS(vector<pair<int,int>>& sources) {
    dist_grid.assign(rows, vector<int>(cols, -1));
    queue<pair<int,int>> bfs;

    for (auto& [r, c] : sources) {
        dist_grid[r][c] = 0;
        bfs.push({r, c});
    }

    while (!bfs.empty()) {
        auto [r, c] = bfs.front();
        bfs.pop();

        for (int d = 0; d < 4; d++) {
            int nr = r + dx[d], nc = c + dy[d];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) 
            continue; //out of bounds

            if (grid[nr][nc] == '#') 
            continue; // wall/blocked cell, adjust to your problem

            if (dist_grid[nr][nc] != -1) 
            continue;

            dist_grid[nr][nc] = dist_grid[r][c] + 1;
            bfs.push({nr, nc});
        }
    }
}

int main() {
    cin >> rows >> cols;
    grid.resize(rows);

    for (auto& row : grid) 
    cin >> row;

    vector<pair<int,int>> sources; // the nodes i can start with
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (grid[i][j] == 'S')  //entries, start nodes
              sources.push_back({i, j}); // adjust source condition

    multiSourceBFS(sources);
    cout << dist_grid[0][1]; // shortest distance you can reach cell (0, 1) from the nearest source
    // dist_grid[r][c] now holds distance to nearest source
}