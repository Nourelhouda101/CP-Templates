#include <bits/stdc++.h>
using namespace std;

int rows, cols;
vector<string> grid;
vector<vector<bool>> vis;

int di[4] = {-1, 1, 0, 0};
int dj[4] = {0, 0, -1, 1};

bool is_valid(int r, int c) {
    return r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] == '.' && !vis[r][c];
}

void dfs(int r, int c) {
    vis[r][c] = true;
    for (int k = 0; k < 4; k++) {
        int nr = r + di[k], nc = c + dj[k];
        
        if (is_valid(nr, nc)) 
        dfs(nr, nc);
    }
}

// The SIZE of each region instead of just the count
int dfsCount(int r, int c) {
    vis[r][c] = true;
    int cnt = 1;
    for (int k = 0; k < 4; k++) {
        int nr = r + di[k], nc = c + dj[k];
        if (is_valid(nr, nc)) 
        cnt += dfsCount(nr, nc);
    }
    return cnt;
}

int main() {
    cin >> rows >> cols;
    grid.resize(rows);
    for (auto& row : grid) cin >> row;
    vis.assign(rows, vector<bool>(cols, false));

    int connected_regions = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (grid[i][j] == '.' && !vis[i][j]) {
                dfs(i, j);
                connected_regions++;
            }

    cout << connected_regions << "\n";
    return 0;
}