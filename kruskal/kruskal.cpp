#include <bits/stdc++.h>
#define INF INT_MAX
using namespace std;

class UnionFind {
    vector<int> ch;
    vector<int> sz;

public:
    UnionFind(int V) {
        ch.resize(V);
        sz.resize(V);

        for (int v = 0; v < V; v++) {
            ch[v] = v;
            sz[v] = 1;
        }
    }

    int find(int v) {
        int v0 = v;
        while (v0 != ch[v0]) {
            v0 = ch[v0];
        }
        return v0;
    }

    void _union(int v0, int w0) {
        if (sz[v0] < sz[w0]) {
            ch[v0] = w0;
            sz[w0] += sz[v0];
        } else {
            ch[w0] = v0;
            sz[v0] += sz[w0];
        }
    }
};

class Edge {
public:
    int v, w; // vertices
    int wt; // peso

    Edge(int v, int w, int wt) {
        this->v = v, this->w = w, this->wt = wt;
    }
};

class UWGraph // undirected weight graph
{
    int V;
    vector<vector<pair<int, int>>> adj; // lista de adjacencia com par (vertice, custo)
    vector<Edge> edges; // lista de arestas

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
        edges.push_back(Edge(u, v, wt));
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

    vector<Edge> kruskal() {
        vector<Edge> e = this->edges;
        sort(e.begin(), e.end(), []( Edge x, Edge y ){ return x.wt < y.wt; });

        vector<Edge> mst;

        UnionFind uf(this->V);
        int k = 0;
        for (int i = 0; k < V-1; ++i) {
            int v0 = uf.find(e[i].v);
            int w0 = uf.find(e[i].w);

            if (v0 != w0) {
                uf._union(v0, w0);
                mst.push_back(e[i]);
                k++;
            }
        }

        return mst;
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
            cout << "-h: mostra o help \n" << 
            "-f <arquivo>: indica o \"arquivo\" que contém o grafo de entrada \n" << 
            "-o <arquivo>: redireciona a saida para o \"arquivo\" \n" <<
            "-s: mostra a solucao \n" << endl;
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

    auto res = g.kruskal();
    auto tree = res;

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

    int wt_sum = 0;

    for (Edge e : tree) {
        wt_sum += e.wt;
    }

    if (solution_flag) {
        if (!path_output.empty()) {
            for (int i = 1; i < tree.size(); i++)
            {
                file_output << "(" << tree[i].v + 1 << "," << tree[i].w + 1 << ")" << " ";
            }
        } else {
            for (int i = 1; i < tree.size(); i++)
            {
                cout << "(" << tree[i].v + 1 << "," << tree[i].w + 1 << ")" << " ";
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