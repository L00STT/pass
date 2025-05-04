#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

void addEdge(vector<vector<int>>& adj, int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void BFS(vector<vector<int>>& adj, int V, int start) {
    vector<bool> visited(V, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u;
        #pragma omp critical
        {
            u = q.front();
            q.pop();
        }
        cout << u << " ";

        #pragma omp parallel for
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (!visited[v]) {
                #pragma omp critical
                {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }
    cout << endl;
}

int main() {
    int V, E;
    cout << "Vertices: "; cin >> V;
    vector<vector<int>> adj(V);

    cout << "Edges: "; cin >> E;
    
    for (int i = 0, u, v; i < E; i++) {
        cin >> u >> v;
        addEdge(adj, u, v);
    }

    cout << "BFS from 0: "; BFS(adj, V, 0);
}