#include <bits/stdc++.h>
#define INF INT_MAX
using namespace std;

struct Compare {
    bool operator()(pair<int, int> a, pair<int, int> b) {
        return a.second > b.second; // ordena a fila de prioridade com base no peso das arestas
    }
};

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

    vector<int> dijkstra_ineficiente(int s) {
        vector<int> pa(V, -1);
        vector<int> dist(V, INF);
        vector<bool> mature(V, false);

        pa[s] = s, dist[s] = 0;


        while (true) {
            int min = INF;
            int y;

            for (int z = 0; z < V; z++) {
                if (mature[z]) continue;
                if (dist[z] < min) {
                    min = dist[z], y = z;
                }
            }
            if (min == INF) break;

            for (auto a : adj[y]) {
                int w = a.first;
                int wt = a.second;
                if (mature[w]) continue;
                if (dist[y] + wt < dist[w]) {
                    dist[w] = dist[y] + wt;
                    pa[w] = y;
                }
            }
            mature[y] = true;
        }

        return dist;
    }

    vector<int> dijkstra_eficiente(int s) {
        vector<int> pa(V, -1), dist(V, INF);
        pa[s] = s, dist[s] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
        pq.emplace(s, 0);

        while (!pq.empty()) {
            auto [u, d] = pq.top();
            pq.pop();

            if (d > dist[u]) continue;

            for (auto &[v, wt] : adj[u]) {
                if (dist[u] + wt < dist[v]) {
                    dist[v] = dist[u] + wt;
                    pa[v] = u;
                    pq.emplace(v, dist[v]);
                }
            }
        }

        return dist;
    }
};

int main(int argc, char *argv[])
{
    string path_input;
    string path_output;
    int v_0 = 0;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            cout << "-h: mostra o help \n" << 
            "-f <arquivo>: indica o \"arquivo\" que contém o grafo de entrada \n" << 
            "-o <arquivo>: redireciona a saida para o \"arquivo\" \n" <<
            "-i <numero>: indica o vertice inicial" << endl;
            return 1;
        }

        if (strcmp(argv[i], "-f") == 0)
        {
            path_input = argv[++i];
        }

        if (strcmp(argv[i], "-o") == 0)
        {
            path_output = argv[++i];
        }

        if (strcmp(argv[i], "-i") == 0)
        {
            v_0 = stoi(argv[++i]) - 1;
        }
    }

    ifstream file_input;

    if (!path_input.empty())
    {
        file_input = ifstream(path_input);

        if (!file_input)
        {
            cerr << "erro ao abrir o arquivo de entrada" << endl;
            return 1;
        }
    }

    int vertices, edges;

    if (!path_input.empty())
    {
        file_input >> vertices >> edges;
    }
    else
    {
        cin >> vertices >> edges;
    }

    UWGraph g(vertices);

    for (int i = 0; i < edges; i++)
    {
        int vertice_1, vertice_2, peso;

        if (!path_input.empty())
        {
            file_input >> vertice_1 >> vertice_2 >> peso;
        }
        else
        {
            cin >> vertice_1 >> vertice_2 >> peso;
        }

        g.addEdge(vertice_1 - 1, vertice_2 - 1, peso);
    }

    auto res = g.dijkstra_eficiente(v_0);

    ofstream file_output;

    if (!path_output.empty())
    {
        file_output = ofstream(path_output);

        if (!file_output)
        {
            cerr << "erro ao abrir o arquivo de saida" << endl;
            return 1;
        }
    }

    if (!path_output.empty()) {
        for (int i = 0; i < res.size(); i++) {
            file_output << i + 1 << ":" << res[i] << " ";
        }

        file_output << endl;
    } else {
        for (int i = 0; i < res.size(); i++) {
            cout << i + 1 << ":" << res[i] << " ";
        }

        cout << endl;
    }
}