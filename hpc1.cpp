#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>
using namespace std;

class Graph{
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V){
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void bfsSequential(int start){
        vector<int> visited(V,0);
        queue<int> q;
        visited[start] = 1;
        q.push(start);

        while (!q.empty()){
            int u = q.front();
            //cout << u << " ";
            q.pop();
            for (int v: adj[u]){
                if (!visited[v]){
                    visited[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    
    void bfsParallel(int start){
        vector<int> visited(V,0);
        queue<int> q;
        visited[start] = 1;
        q.push(start);

        while (!q.empty()){
            int size = q.size();
            vector<int> currentLevel;

            for (int i = 0; i < size; i++){
                int u = q.front(); q.pop();
                currentLevel.push_back(u);
            }

            #pragma omp parallel for
            for (int i = 0; i < currentLevel.size(); i++){
                int u = currentLevel[i];
                //cout << u << " ";

                for (int v: adj[u]){
                    if (!visited[v]){
                        #pragma omp critical
                        if (!visited[v]){
                            visited[v] = 1;
                            q.push(v);
                        }
                    }
                }
            }
        }
    }

    void dfsSequential(int start, vector<int> &visited){
        if (visited[start] == 1) return;
        visited[start] = 1;
        //cout << start << " ";
        for (int v: adj[start]){
            if (!visited[v])
                dfsSequential(v,visited);
        }
    }

    void dfsParallel(int start, vector<int> &visited){
        if (visited[start] == 1) return;
        visited[start] = 1;
        cout << start << " ";
        
        #pragma omp parallel for
        for (int i = 0; i < adj[start].size(); i++){
            int v = adj[start][i];
            #pragma omp critical
            if (!visited[v]){
                #pragma omp task
                dfsParallel(v,visited);
            }
        }
    }
};

int main() {
    int V = 10000; // Adjust for larger graphs
    Graph g(V);

    // Add random edges (sparse graph)
    for (int i = 0; i < V - 1; ++i) {
        g.addEdge(i, i + 1);
        if (i + 10 < V) g.addEdge(i, i + 10);  // to increase branching
    }
    // Graph g(5);
    // g.addEdge(0, 1);
    // g.addEdge(0, 2);
    // g.addEdge(0, 3);
    // g.addEdge(2, 1);
    // g.addEdge(2, 4);
    double start_par_bfs = omp_get_wtime();
    g.bfsParallel(0);
    double end_par_bfs = omp_get_wtime();
    cout << "\nTime taken (Parallel BFS): " << (end_par_bfs - start_par_bfs) << " seconds\n\n";

    double start_seq_bfs = omp_get_wtime();
    g.bfsSequential(0);
    double end_seq_bfs = omp_get_wtime();
    cout << "\nTime taken (Sequential BFS): " << (end_seq_bfs - start_seq_bfs) << " seconds\n\n";
    // vector<int> visited(5,0);
    // g.dfsParallel(0,visited);
    return 0;
}
