#include <vector>
#include <iostream>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;

class Graph
{
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    void print()
    {
        for (int i = 1; i < V; i++)
        {
            std::cout << "Vértice " << i << ":";
            for (int adj : adj[i])
            {
                std::cout << " -> " << adj;
            }
            std::cout << std::endl;
        }
    }

    Graph reverse()
    {
        Graph newGraph(this->V);

        for (int i = 1; i < V; i++)
        {
            for (int adj : adj[i])
            {
                newGraph.addEdge(adj, i);
            }
        }

        return newGraph;
    }

    void dfsRpost(vector<vector<int>> adjList, int v, bool visited[], vector<int> &post)
    {
        visited[v] = true;

        for (int a : adjList[v])
        {
            if (visited[a] != true)
            {
                dfsRpost(adjList, a, visited, post);
            }
        }

        post.insert(post.begin(), v);
    }

    void dfsRsccs(vector<vector<int>> adjList, int v, bool visited[], vector<int> &scc)
    {
        visited[v] = true;
        scc.push_back(v);

        for (int a : adjList[v])
        {
            if (visited[a] != true)
            {
                dfsRsccs(adjList, a, visited, scc);
            }
        }
    }

    vector<vector<int>> findSCCs()
    {
        Graph reverseGraph = this->reverse();

        bool visited[this->V];
        for (bool v : visited)
            v = false;

        vector<int> post;

        for (int v = 1; v < this->V; v++)
        {
            if (!visited[v])
            {
                dfsRpost(reverseGraph.adj, v, visited, post);
            }
        }

        for (int i = 1; i < V; i++)
        {
            visited[i] = false;
        }

        vector<vector<int>> sccs;

        for (int p : post)
        {
            if (!visited[p])
            {
                vector<int> scc;
                dfsRsccs(adj, p, visited, scc);
                sccs.push_back(scc);
            }
        }

        return sccs;
    }
};

int main(int argc, char *argv[])
{
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

    int vertices, edges;

    if (file_input)
    {
        file_input >> vertices >> edges;
    }
    else
    {
        cin >> vertices >> edges;
    }

    Graph graph(vertices + 1);

    for (int i = 0; i < edges; i++)
    {
        int vertice_1, vertice_2;

        if (file_input)
        {
            file_input >> vertice_1 >> vertice_2;
        }
        else
        {
            cin >> vertice_1 >> vertice_2;
        }

        graph.addEdge(vertice_1, vertice_2);
    }

    vector<vector<int>> sccs = graph.findSCCs();

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

    for (vector<int> scc : sccs)
    {
        for (int i : scc)
        {
            if (!path_output.empty())
            {
                file_output << i << " ";
            }
            else
            {
                cout << i << " ";
            }
        }
        if (!path_output.empty())
        {
            file_output << endl;
        }
        else
        {
            cout << endl;
        }
    }

    return 0;
}