#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <vector>


class Graph
{
private:
    std::vector<std::vector<int> > graph;
    int qtdVertices;
    int qtdArestas;
public:
    Graph(int n);
    Graph();
    ~Graph();

    void add_aresta(int v, int u);
    void remove_aresta(int v, int u);
    void clear_arestas();
    void add_all_vertice(int n); // add de 0 até n-1
    bool possui_aresta(int v, int u);
    int grau(int v);

    const std::vector<int> adjList(int v);
    int getQtdVertices(){ return qtdVertices; }
    int getQtdArestas(){ return qtdArestas; }
};


#endif