#include <iostream>
#include <list>
#include <stack>
#include <vector>

using namespace std;

class Graph {
    int V;      
    vector<int> *adj;
    void DFSUtil(int v, bool visited[], bool output, stack<int> *Stack = nullptr);

public:
    Graph(int V);
    void addEdge(int v, int w);
    Graph getTranspose();
    void findSCCs();
};

Graph::Graph(int V) {
    this->V = V;
    adj = new vector<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

void Graph::DFSUtil(int v, bool visited[], bool output, stack<int> *Stack) {
    visited[v] = true;
    
    if (output) 
        cout << v << " ";
    
    cout << v;

    for (int i : adj[v]) {
        if (!visited[i])
            DFSUtil(i, visited, output, Stack);
    }

    if (Stack != nullptr) {
        Stack->push(v);
    }
}

Graph Graph::getTranspose() {
    Graph g_t(V);

    for (int v = 0; v < V; v++) {
        for (int i : adj[v]) {
            g_t.adj[i].push_back(v);
        }
    }

    return g_t;
}

void Graph::findSCCs() {
    stack<int> Stack;

    bool *visited = new bool[V];
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }

    for (int i = 0; i < V; i++) {
        if (visited[i] == false) {
            DFSUtil(i, visited, false, &Stack);
        }
    }

    Graph g_t = getTranspose();

    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }

    while (!Stack.empty()) {
        int v = Stack.top();
        Stack.pop();

        if (!visited[v]) {
            g_t.DFSUtil(v, visited, true);
            cout << endl;
        }
    }

    delete[] visited;
}

int main() {
    int v_size, e_size;

    cin >> v_size >> e_size;

    Graph g(v_size);

    for (int i = 0; i < e_size; i++) {
        int v_1, v_2;
        cin >> v_1 >> v_2;
        g.addEdge(v_1, v_2);
    }

    cout << "Componentes fortemente conectados no grafo:\n";
    g.findSCCs();
}