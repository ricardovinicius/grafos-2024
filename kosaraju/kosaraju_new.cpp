#include <vector>
#include <iostream>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }    

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    void print()
    {
        for (int i = 0; i < V; i++) {
            std::cout << "Vértice " << i << ":";
            for (int adj : adj[i]) {
                std::cout << " -> " << adj;
            }
            std::cout << std::endl;
        }
    }

    Graph reverse() {
        Graph newGraph(this->V);
        
        for (int i = 0; i < V; i++) {
            for (int adj : adj[i]) {
                newGraph.addEdge(adj, i);
            }
        }

        return newGraph;
    }

    void dfsRpost(vector<vector<int>> adjList, int v, bool visited[], vector<int> &post) {
        visited[v] = true;

        for (int a : adjList[v]) {
            if (visited[a] != true) {
                dfsRpost(adjList, a, visited, post);
            }
        }

        post.insert(post.begin(), v);
    }

    void dfsRsccs(vector<vector<int>> adjList, int v, bool visited[]) {
        visited[v] = true;
        cout << v << " ";

        for (int a : adjList[v]) {
            if (visited[a] != true) {
                dfsRsccs(adjList, a, visited);
            }
        }
    }

    void findSCCs() {
        Graph reverseGraph = this->reverse();

        bool visited[this->V];
        for (bool v : visited) v = false;

        vector<int> post;

        for (int v = 0; v < this->V; v++) {
            if (!visited[v]) {
                dfsRpost(reverseGraph.adj, v, visited, post);
            }
        }

        for (int i = 0; i < V; i++) {
            visited[i] = false;
        }

        for (int p : post) {
            if (!visited[p]) {
                dfsRsccs(adj, p, visited);
                cout << endl;
            }
        }
    }
};

int main() {
    int vertices, edges;
    cin >> vertices >> edges;
    Graph graph(vertices + 1);

    for (int i = 0; i < edges; i++) {
        int vertice_1, vertice_2;
        cin >> vertice_1 >> vertice_2;

        graph.addEdge(vertice_1, vertice_2);
    }

    graph.findSCCs();

    return 0;
}