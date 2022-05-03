#include "graph.hpp"

Graph::Graph(int n)
{
    // graph = new std::vector<std::vector<int> >(n, std::vector<int>());
    qtdVertices = n;
    qtdArestas = 0;
    for(int i = 0; i < n; ++i){
        graph.push_back(std::vector<int>());
    }
}

Graph::Graph()
{
    // graph = new std::vector<std::vector<int> >(n, std::vector<int>());
    qtdVertices = 0;
    qtdArestas = 0;
}


Graph::~Graph()
{
    // delete graph;
}

void Graph::add_aresta(int v, int u)
{
    graph[v].push_back(u);
    graph[u].push_back(v);
    ++qtdArestas;
}

void Graph::remove_aresta(int v, int u)
{
    std::vector<int>::iterator it;

    it = graph[v].begin();
    while(it != graph[v].end() && *it != u){
        ++it;
    }
    graph[v].erase(it);

    it = graph[u].begin();
    while(it != graph[u].end() && *it != v){
        ++it;
    }
    graph[u].erase(it);

    --qtdArestas;
}

void Graph::add_all_vertice(int n)
{
    for(int i=0; i < n; ++i){
        graph.push_back(std::vector<int>());
    }
    qtdVertices = n;
}

const std::vector<int> Graph::adjList(int v)
{
    return graph[v];
}

bool Graph::possui_aresta(int v, int u)
{  
    for(int x : adjList(v)){
        if(x == u){
            for(int y : adjList(u)){
                if(y == v){
                    return true;
                }
            }
        }
    }
    return false;
}

int Graph::grau(int v)
{
    return graph[v].size();
}

void Graph::clear_arestas()
{
    for(int i=0; i< getQtdVertices(); ++i){
        graph[i].clear();
    }
    qtdArestas = 0;
}