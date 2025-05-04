#include<bits/stdc++.h>
#include <omp.h>
using namespace std;

void addEdge(vector<vector<int>> &adj, int u, int v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void DFS(vector<vector<int>> &adj, int V, int start){
    vector<bool> visited(V, false);
    stack<int> s;
    visited[start] = true;
    s.push(start);

    while(!s.empty()){
        int u;
        #pragma omp critical
        {
            u = s.top();
            s.pop();
        }
        cout << u << " ";

        #pragma omp parallel for
        for(int i = adj[u].size() - 1; i >= 0; i--){ // reverse to match recursive DFS order
            int v = adj[u][i];
            if(!visited[v]){
                #pragma omp critical
                {
                    if(!visited[v]){
                        visited[v] = true;
                        s.push(v);
                    }
                }
            }
        }
    }
    cout << endl;
}

int main(){
    int V;
    cout << "Enter the vertices: ";
    cin >> V;
    int E;
    cout << "Enter the edges: ";
    cin >> E;

    vector<vector<int>> adj(V);
    for(int i = 0; i < E; i++){
        int u, v;
        cin >> u >> v;
        addEdge(adj, u, v);
    }

    // cout << "BFS from 0: ";
    // BFS(adj, V, 0);

    cout << "DFS from 0: ";
    DFS(adj, V, 0);
}
