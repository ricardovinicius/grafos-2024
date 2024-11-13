#include <bits/stdc++.h>
#define INF 2147483647
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

        priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
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

int main(int argc, char *argv[])
{
    string path_input;
    string path_output;
    bool solution_flag = false;
    int v_0 = 0;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            cout << "ajuda" << endl;
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

        if (strcmp(argv[i], "-s") == 0)
        {
            solution_flag = true;
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

    auto res = g.prim(v_0);
    auto tree = res.first;
    int wt_sum = res.second;

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

    if (solution_flag) {
        if (!path_output.empty()) {
            for (int i = 1; i < tree.size(); i++)
            {
                file_output << "(" << i + 1 << "," << tree[i] + 1 << ")" << " ";
            }
        } else {
            for (int i = 1; i < tree.size(); i++)
            {
                cout << "(" << i + 1 << "," << tree[i] + 1 << ")" << " ";
            }
        }

        cout << endl;
    } else {
        if (!path_output.empty()) {
            file_output << wt_sum << endl;
        } else {
            cout << wt_sum << endl;
        }
    }
}