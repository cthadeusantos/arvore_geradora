#include "opBasic.hpp"
#include <stack>
#include <queue>

#include <iostream>

#include "frontier.hpp"

bool OpBasic::cyclic(Graph& g, int v)
{
    std::stack<int> my_stack;
    bool visitados[g.getQtdVertices()];
    int prox_vizinho[g.getQtdVertices()];
    int anterior[g.getQtdVertices()];
    for(int i=0; i < g.getQtdVertices(); ++i){
        visitados[i]=false;
        prox_vizinho[i]=0;
        anterior[i]=-1;
    }
    int topo = v;
    int next;
    my_stack.push(topo);
    visitados[topo] = true;
    while(not my_stack.empty() ){
        topo = my_stack.top();
        if(prox_vizinho[topo] == g.grau(topo)){
            my_stack.pop();
        }else{
            next = g.adjList(topo)[prox_vizinho[topo]];
            ++prox_vizinho[topo];
            if(anterior[topo] != next){
                if( visitados[next] ){
                    return true; // POSSUI CICLO
                }
                visitados[next] = true;
                anterior[next] = topo;
                my_stack.push(next);
            }
        }
    }
    return false;
}

bool OpBasic::is_cyclic(Graph& g){
    
    for(int i=0; i < g.getQtdVertices(); ++i){
        if( cyclic(g, i) ){
            return true; // TEM CICLO
        }
    }
    return false;
}

bool OpBasic::is_tree(Graph& g)
{
    if( not is_cyclic(g) && g.getQtdArestas() == g.getQtdVertices()-1 ){
        return true;
    }
    return false;
}

std::vector<int> OpBasic::diference_edge(Graph& g, Graph& t)
{
    //std::tuple<int, int> list;
    std::vector<int> list;
    for(int i=0; i < t.getQtdVertices(); ++i){
        for(int j=i+1; j < t.getQtdVertices(); ++j){
            if( g.possui_aresta(i, j) && not t.possui_aresta(i,j) ){
                list.push_back(i);
                list.push_back(j);
            }
        }
    }
    return list;
}

int OpBasic::distance(Graph& g, int v, int u)
{
    if(v == u){
        return 0;
    }
    std::queue<int> fila;
    int tam = g.getQtdVertices(); 
    int dist[tam];
    for(int i=0; i < tam; ++i){
        dist[i] = -1;
    }
    dist[v] = 0;
    fila.push(v);
    int first;
    while( not fila.empty() ){
        first = fila.front();
        for(int x : g.adjList(first) ){
            if( dist[x] == -1 ){
                dist[x] = dist[first] + 1;
                fila.push(x);
            }
        }
        fila.pop();
    }
    return dist[u];
}

std::vector<std::vector<int> > OpBasic::distance(Graph& g, int v)
{
    std::vector<std::vector<int> > caminhos(g.getQtdVertices(), std::vector<int>(g.getQtdVertices(), -1));
    for(int i=0; i < g.getQtdVertices(); ++i){
        caminhos[i] = short_path(g, v, i);
    }

    return caminhos;
}

std::vector<int> OpBasic::short_path(Graph& g, int begin, int end)
{
    std::vector<int> my_stack;
    if(begin == end){
        return my_stack;
    }
    int ordem = g.getQtdVertices();
    std::vector<int> path(ordem, -1);
    
    // bool visitados[ordem];
    int prox_vizinho[ordem];
    int anterior[ordem];
    for(int i=0; i < ordem; ++i){
        // visitados[i]=false;
        prox_vizinho[i]=0;
        anterior[i]=-1;
    }
    int topo = begin;
    int next;
    my_stack.push_back(topo);
    // visitados[topo] = true;

    while(not my_stack.empty() ){
        topo = my_stack.back();
        if(topo == end){
            if( my_stack.size() < path.size() ){
                path = my_stack;
            }
            my_stack.pop_back();
        }
        else
        if(prox_vizinho[topo] == g.grau(topo)){
            my_stack.pop_back();
            prox_vizinho[topo] = 0;
        }else{
            next = g.adjList(topo)[prox_vizinho[topo]];
            ++prox_vizinho[topo];
            if(anterior[topo] != next){
                if( not pertence(next, my_stack) ){
                    anterior[next] = topo;
                    my_stack.push_back(next);
                }
                /*
                if( visitados[next] ){
                    return true; // POSSUI CICLO
                }

                visitados[next] = true;
                anterior[next] = topo;
                my_stack.push_back(next);
                */
            }
        }
    }
    //path.erase(path.begin());
    return path;
}

int OpBasic::girth(Graph& g)
{
    int grt = INF_VALUE;
    int ordem = g.getQtdVertices();
    int parent[ordem];
    int distance[ordem];
    std::vector<int> pilha;
    std::queue<int> fila;
    for(int i=0; i < ordem; ++i){
        parent[i]=-1;
        distance[i]=0;
    }

    for(int v=0; v < ordem; ++v){
        pilha.clear();
        fila.push(v);
        parent[v] = -1;
        distance[v] = 0;
        while( not fila.empty() ){
            int atual = fila.front();
            fila.pop();
            pilha.push_back(atual);
            for(int u : g.adjList(atual)){
                if(u != parent[atual]){
                    if( not pertence(u, pilha) ){
                        parent[u] = atual;
                        distance[u] = distance[atual] + 1;
                        fila.push(u);
                    }else{
                        int small = distance[atual] + distance[u] + 1;
                        if(small < grt){
                            grt = small;
                        }
                    }
                }
            }
        }
    }
    return grt;
}

void OpBasic::clear(std::queue<int>& q)
{
    while(not q.empty()){
        q.pop();
    }
}
void OpBasic::clear(std::stack<int>& s)
{
    while(not s.empty()){
        s.pop();
    }
}

bool OpBasic::pertence(int x, std::vector<int>& v)
{
    for(int i : v){
        if(i == x){
            return true;
        }
    }
    return false;
}

std::vector<int> OpBasic::centers(Graph& g)
{
    int ordem = g.getQtdVertices();
    std::vector<int> matrix(ordem*ordem, 0);
    for(int v=0; v < ordem; ++v){
        for(int u=v+1; u< ordem; ++u){
            matrix[ordem*v+u] = distance(g, v, u);
            matrix[ordem*u+v] = distance(g, v, u);
        }
    }

    int max[ordem];
    for(int v=0; v < ordem; ++v){
        int maior;
        maior = 0;
        for(int u=0; u< ordem; ++u){
            if(matrix[ordem*v+u] > maior){
                maior = matrix[ordem*v+u];
            }
        }
        max[v] = maior;
    }
    
    int min = max[0];
    for(int i=1; i < ordem; ++i){
        if(max[i] < min){
            min = max[i];
        }
    }

    std::vector<int> center;
    for(int i=0; i< ordem; ++i){
        if(max[i] == min){
            center.push_back(i);
        }
    }

    return center;
}

int OpBasic::diameter(Graph& g)
{
    int maior = 0;
    for(int v=0; v < g.getQtdVertices(); ++v){
        for(int u=v+1;u < g.getQtdVertices(); ++u){
            int d = distance(g, v, u);
            if(d > maior){
                maior = d;
            }
        }
    }
    return maior;
}

int OpBasic::min_diameter_tree_value(Graph& g)
{
    std::vector<int> center = centers(g);
    Graph tree(g.getQtdVertices() );
    int min_diameter = INF_VALUE;
    int diameter;
    std::vector<int> path;
    std::vector<std::vector<int> > caminhos(g.getQtdVertices(), std::vector<int>());
    for(int c : center){
        caminhos = distance(g, c);
        for(int v=0; v < g.getQtdVertices(); ++v){
            if(c != v){
                for(int i=0; i < caminhos[v].size()-1; ++i){
                    int x = caminhos[v][i];
                    int y = caminhos[v][i+1];
                    if(not tree.possui_aresta(x, y) ){
                        tree.add_aresta(x, y);
                    }
                }
            }
        }

        diameter = OpBasic::diameter(tree);
        // std::cout << "diameter = " << diameter << std::endl;
        if(diameter < min_diameter){
            min_diameter = diameter;
        }

        tree.clear_arestas();
        path.clear();
        for(int i=0; i < g.getQtdVertices(); ++i){
            caminhos[i].clear();
        }
        
    }
    return min_diameter;
}