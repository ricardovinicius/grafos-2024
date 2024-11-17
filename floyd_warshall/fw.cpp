/*
Implementação do algoritmo Floyd-Warshall 
para encontrar o tamanho das menores distância entre 
vértices de um grafo direcionado e com pesos positivos
*/

#include <bits/stdc++.h>
#define INF INT_MAX
using namespace std;

class WGraph // direct weight graph
{
    int V;
    vector<vector<int>> adj; // matriz de adjacencia com par (vertice, custo)

public:
    WGraph(int V) {
        this->V = V;
        for (int i = 0; i < V; i++) {
            adj.push_back(vector<int>(V, 0));
        }
    }

    void addEdge(int i, int j, int wt) {
        adj[i][j] = wt;
    }

    void print() {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++)
                if (adj[i][j] != INF)
                    cout << adj[i][j] << " ";
                else
                    cout << "INF" << " ";
            cout << "\n";
        }
    }

    vector<vector<int>> floyd_warshall() {
        vector<vector<int>> dist = adj; // cria uma copia da matriz de adj 

        int i, j, k;

        for (k = 0; k < V; k++) {
            for (i = 0; i < V; i++) {
                for (j = 0; j < V; j++) {
                    if (dist[k][j] != INF && dist[i][k] != INF)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        return dist;
    }
};

int main(int argc, char *argv[]) {
    string path_input;
    string path_output;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            cout << "-h: mostra o help \n" << 
            "-f <arquivo>: indica o \"arquivo\" que contém o grafo de entrada \n" << 
            "-o <arquivo>: redireciona a saida para o \"arquivo\" \n" << endl;
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

    int vertices;

    if (!path_input.empty())
    {
        file_input >> vertices;
    }
    else
    {
        cin >> vertices;
    }

    WGraph g(vertices);

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            int wt; // entra -1 se for infinito
            if (!path_input.empty())
            {
                file_input >> wt;
            }
            else
            {
                cin >> wt;
            }
            if (wt == -1) {
                g.addEdge(i, j, INF);
            }
            else {
                g.addEdge(i, j, wt);
            }
                
        }  
    }

    auto sol = g.floyd_warshall();

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

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++)
            if (sol[i][j] != INF) {
                if (!path_output.empty()) 
                    file_output << sol[i][j] << " ";
                else
                    cout << sol[i][j] << " ";
            }
            else {
                if (!path_output.empty()) 
                    file_output << "INF" << " ";
                else
                    cout << "INF" << " ";
            }
        if (!path_output.empty()) 
            file_output << endl;
        else
            cout << endl;
    }
}