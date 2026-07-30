#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define ll long long
#define sp " "

vector<int> get_neighbors(int state) {
    vector<int> neighbors;
    // generate valid next-states from 'state' according to problem rules
    // example placeholder: state+1, state-1, state*2
    neighbors.push_back(state - 1);
    neighbors.push_back(state * 2);
    return neighbors;
}

bool is_valid(int state) {
    // problem-specific bounds/validity check
    return state >= 0 && state <= 10000;
}

int bfs_implicit(int start, int target, int upperbound) {
    // unordered_map<int, int> dist; // state -> distance
    // use map if indicies are huge or on strings
    vector<int>dist(upperbound + 1, -1);
    queue<int> bfs;

    dist[start] = 0;
    bfs.push(start);

    while (!bfs.empty()) {
        int u = bfs.front();
        bfs.pop();

        if (u == target) return dist[u];

        for (int v : get_neighbors(u)) {
            if (!is_valid(v)) 
            continue;

            if (dist[v] != -1) 
            continue; // already visited

            dist[v] = dist[u] + 1;
            bfs.push(v);
        }
    }
    return -1; // unreachable
}

int main() {
    ll start, target;
    cin >> start >> target;
    cout << bfs_implicit(start, target, 10000);
}