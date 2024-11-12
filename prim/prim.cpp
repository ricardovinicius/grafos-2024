#include <bits/stdc++.h>
using namespace std;

class UWGraph // undirected weight graph
{
    int V;
    vector<vector<pair<int, int>>> adj; // lista de adjacencia com par (vertice, custo)

public:

    UWGraph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int wt) {
        adj[u].push_back(make_pair(v, wt));
        adj[v].push_back(make_pair(u, wt));
    }

    void printGraph() {
        for (int u = 0; u < V; u++) {
            cout << "Edges of " << u << ":" << endl;

            for (auto v : adj[u]) {
                cout << "\tNode " << v.first << " with weight " << v.second << endl;
            }
        }
    }

    vector<int> mst() {
        vector<int> pa(this->V);
        for (int i = 0; i < V; i++) {
            pa[i] = -1;
        }

        pa[0] = 0;
        while (true) {
            int min = 2147483647;

            int x, y;
            for (int i = 0; i < this->V; i++) {
                if (pa[i] == -1) continue;
                for (auto v : adj[i]) {
                    if (pa[v.first] == -1 && v.second < min) {

                        min = v.second;
                        x = i, y = v.first;
                    }
                }
            }

            if (min == 2147483647) break;
            pa[y] = x;
        } 

        return pa;
    }
};

int main() {
    int V = 8;
    UWGraph graph(V);

    graph.addEdge(5, 4, 35);
    graph.addEdge(7, 4, 37);
    graph.addEdge(7, 5, 28);
    graph.addEdge(0, 7, 16);
    graph.addEdge(1, 5, 32);
    graph.addEdge(0, 4, 38);
    graph.addEdge(2, 3, 17);
    graph.addEdge(7, 1, 19);
    graph.addEdge(0, 2, 26);
    graph.addEdge(1, 2, 36);
    graph.addEdge(1, 3, 29);
    graph.addEdge(7, 2, 34);
    graph.addEdge(2, 6, 40);
    graph.addEdge(3, 6, 52);
    graph.addEdge(0, 6, 58);
    graph.addEdge(6, 4, 93);
    graph.printGraph();

    auto res = graph.mst();
    
    for (int i = 0; i < res.size(); i++) {
        cout << i << "->" << res[i] << " ";
    }
}