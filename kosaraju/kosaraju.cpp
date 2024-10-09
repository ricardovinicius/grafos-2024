#include <iostream>
#include <list>
#include <map>
#include <stack>
using namespace std;

class Graph {
    int V;

    map<int, list<int> >
        adjList; // Adjacency list to store the graph

public:
    Graph(int V) {
        this->V = V;
    }

    // Function to add an edge between vertices u and v of
    // the graph
    void add_edge(int u, int v)
    {
        adjList[u].push_back(v);
    }

    // Function to print the adjacency list representation
    // of the graph
    void print()
    {
        cout << "Adjacency list for the Graph: " << endl;
        // Iterate over each vertex
        for (auto i : adjList) {
            // Print the vertex
            cout << i.first << " -> ";
            // Iterate over the connected vertices
            for (auto j : i.second) {
                // Print the connected vertex
                cout << j << " ";
            }
            cout << endl;
        }
    }

    void DFSUtil(map<int, list<int>>adjList, int v, bool visited[], stack<int> *Stack)
    {
        visited[v] = true;
        
        if (Stack == nullptr) {
            cout << v << " ";
        }
            
        for (int i : adjList[v])
            if (visited[i] == false)
                DFSUtil(adjList, i, visited, Stack);

        if (Stack != nullptr) {
            Stack->push(v);
        }
    }

    Graph getTranspose() {
        Graph g(V);

        for (int v = 1; v < V + 1; v++) {
            for (int i : adjList[v]) {
                g.add_edge(i, v);
            }
        }

        return g;
    }

    void findSCCs() {
        stack<int> Stack;

        bool visited[V + 1];
        for (int i = 1; i < V + 1; i++)
            visited[i] = false;

        for (int i = 1; i < V + 1; i++) {
            if (!visited[i]) {
                DFSUtil(adjList, i, visited, &Stack);
                cout << endl;
            }
        }    

        Graph g_t = getTranspose();

        for (int i = 1; i < V + 1; i++)
            visited[i] = false;

        while (!Stack.empty()) {
            int v = Stack.top();
            Stack.pop();

            if (!visited[v]) {
                g_t.DFSUtil(g_t.adjList, v, visited, nullptr);
                cout << endl;
            }
        }
    }
};

int main()
{
    int vertices, edges;
    cin >> vertices >> edges;

    Graph g(vertices);

    cout << vertices << " " << edges << endl;

    for (int i = 0; i < edges; i++) {
        int vertice_1, vertice_2;
        cin >> vertice_1 >> vertice_2;

        g.add_edge(vertice_1, vertice_2);
    }

    g.findSCCs();
    return 0;
}
