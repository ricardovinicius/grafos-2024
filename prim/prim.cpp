#include <bits/stdc++.h>
#define INF 2147483647
using namespace std;

class UWGraph // undirected weight graph
{
    int V;
    vector<vector<pair<int, int>>> adj; // lista de adjacencia com par (vertice, custo)

public:
    UWGraph(int V)
    {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int wt)
    {
        adj[u].push_back(make_pair(v, wt));
        adj[v].push_back(make_pair(u, wt));
    }

    void printGraph()
    {
        for (int u = 0; u < V; u++)
        {
            cout << "Edges of " << u << ":" << endl;

            for (auto v : adj[u])
            {
                cout << "\tNode " << v.first << " with weight " << v.second << endl;
            }
        }
    }

    pair<vector<int>, int> prim(int v_0)
    {
        vector<int> custo(this->V);
        vector<int> prev(this->V);

        for (int i = 0; i < V; i++)
        {
            custo[i] = INF;
            prev[i] = -1;
        }

        custo[v_0] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<bool> visited(this->V, false);

        for (int i = 0; i < custo.size(); i++)
        {
            pq.push(make_pair(i, custo[i]));
        }

        int wt_sum = 0;

        while (!pq.empty())
        {
            pair<int, int> v = pq.top();
            pq.pop();

            int u = v.first;
            int wt = v.second;

            if (visited[u] == true)
            {
                continue;
            }

            wt_sum += wt;
            cout << wt << endl;
            visited[u] = true;

            for (auto w : adj[u])
            {
                if (visited[w.first] == false && custo[w.first] > w.second)
                {
                    custo[w.first] = w.second;
                    pq.push(make_pair(w.first, w.second));
                    prev[w.first] = v.first;
                }
            }
        }

        return make_pair(prev, wt_sum);
    }
};

int main()
{
    int V = 8; // Temos 8 vértices (0 a 7)

    UWGraph g(V);

    // Adicionando as arestas e seus pesos
    g.addEdge(5, 4, 35); // Aresta 5-4 com peso 35
    g.addEdge(7, 4, 37); // Aresta 7-4 com peso 37
    g.addEdge(7, 5, 28); // Aresta 7-5 com peso 28
    g.addEdge(0, 7, 16); // Aresta 0-7 com peso 16
    g.addEdge(1, 5, 32); // Aresta 1-5 com peso 32
    g.addEdge(0, 4, 38); // Aresta 0-4 com peso 38
    g.addEdge(2, 3, 17); // Aresta 2-3 com peso 17
    g.addEdge(7, 1, 19); // Aresta 7-1 com peso 19
    g.addEdge(0, 2, 26); // Aresta 0-2 com peso 26
    g.addEdge(1, 2, 36); // Aresta 1-2 com peso 36
    g.addEdge(1, 3, 29); // Aresta 1-3 com peso 29
    g.addEdge(7, 2, 34); // Aresta 7-2 com peso 34
    g.addEdge(2, 6, 40); // Aresta 2-6 com peso 40
    g.addEdge(3, 6, 52); // Aresta 3-6 com peso 52
    g.addEdge(0, 6, 58); // Aresta 0-6 com peso 58
    g.addEdge(6, 4, 93); // Aresta 6-4 com peso 93

    auto res = g.prim(0);
    auto tree = res.first;
    int wt_sum = res.second;

    for (int i = 1; i < tree.size(); i++)
    {
        cout << i << "->" << tree[i] << " ";
    }

    cout << endl
         << "soma dos pesos: " << wt_sum << endl;
}