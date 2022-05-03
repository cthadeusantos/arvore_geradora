#include "strech.hpp"
#include "opBasic.hpp"
#include "frontier.hpp"

void Strech::find_index(Graph& g)
{
    int prox_vizinho[g.getQtdVertices()];
    int ult_colocado[g.getQtdVertices()];
    int v = 0;
    int u;
    int arv = 0;
    int grt;

    index = INF_VALUE;

    OpBasic op;

    grt = op.girth(g);

    Graph tree(g.getQtdVertices());

    for(int i=0; i < g.getQtdVertices(); ++i){
        prox_vizinho[i] = 0;
        ult_colocado[i] = -1;
    }

    while( v >= 0 ){
        if( prox_vizinho[v] == g.grau(v) ){
            prox_vizinho[v] = 0;
            --v;
            if(v < 0) break; // acaba o algoritmo
            tree.remove_aresta(v, ult_colocado[v]);
            ult_colocado[v] = -1;

        }else{
            u = g.adjList(v)[prox_vizinho[v]];
            ++prox_vizinho[v];
            if( not tree.possui_aresta(v, u) ){
                tree.add_aresta(v, u);
                ult_colocado[v] = u;
                if(not OpBasic::is_cyclic(tree)){
                    if(tree.getQtdArestas() == tree.getQtdVertices()-1){
                        int f = find_factor(g, tree);
                        ++arv;
                        if(f < index){
                            index = f;
                            this->tree = tree;
                            if(index == grt-1){// alteracao LF
                              break;// alteracao LF
                            }// alteracao LF
                        }
                    }else{
                        ++v;
                        continue;
                    }
                }
                tree.remove_aresta(v, u);
            }
        }
    }

    this->total_arv = arv;
}

void Strech::find_index_pararell(Graph& g, int raiz, int start, int end)
{
    int prox_vizinho[g.getQtdVertices()];
    int ult_colocado[g.getQtdVertices()];
    int v = raiz;
    int u;
    // int arv = 0; // debug
    index = INF_VALUE;

    Graph tree(g.getQtdVertices());

    for(int i=0; i < g.getQtdVertices(); ++i){
        prox_vizinho[i] = 0;
        ult_colocado[i] = -1;
    }

    prox_vizinho[v] = start;

    while( true ){
        if(v == raiz){
            if(prox_vizinho[v] == end){
                break; // Fim do algoritmo
            }
        }

        if( prox_vizinho[v] == g.grau(v) ){
            prox_vizinho[v] = 0;
            v = g.ant_vertex(v);
            // if(v < 0) break; // acaba o algoritmo
            tree.remove_aresta(v, ult_colocado[v]);
            ult_colocado[v] = -1;

        }else{
            u = g.adjList(v)[prox_vizinho[v]];
            ++prox_vizinho[v];
            if( not tree.possui_aresta(v, u) ){
                tree.add_aresta(v, u);
                ult_colocado[v] = u;
                if(not OpBasic::is_cyclic(tree)){
                    if(tree.getQtdArestas() == tree.getQtdVertices()-1){
                        int f = Strech::find_factor(g, tree);
                        // ++arv;
                        if(f < index){
                            //mtx.lock(); // LOCK

                            this->index = f;
                            this->tree = tree;
                            //mtx.unlock(); // NU_LOCK
                        }
                    }else{
                        v = g.next_vertex(v);
                        continue;
                    }
                }
                tree.remove_aresta(v, u);
            }
        }
    }
    // std::cout << "total arv = " << arv << std::endl;
}

// CONTINUAR AQUI
void Strech::find_index_thread(Graph& g)
{

    int raiz = -1;
    for(int i=0; i < g.getQtdVertices(); ++i){
        if(g.grau(i) > raiz){
            raiz = i;
        }
    }

    find_index_pararell(g, raiz, 0, g.adjList(raiz).size());
/*
    //std::thread vetor_th[g.adjList(raiz).size()];
    int limite = g.adjList(raiz).size()-1;
    for(int i=0; i < limite; ++i){
        //vetor_th[i] = std::thread(&Strech::find_index_pararell, this, g, raiz, i, i+1);
    }

    for(int i=0; i < limite; ++i){
        vetor_th[i].join();
    }
*/
    /*
    for(int v=0; v < limite; ++v){
        vetor_th.push_back(std::thread (&Strech::find_index_pararell, this, g, raiz, v, v+1) );
        // vetor_th.push_back(std::thread (g, raiz, v, v+1)  );
    }

    for(auto& h : vetor_th){
        h.join();
    }
    */
}

int Strech::find_factor(Graph& g, Graph& tree)
{
    std::vector<int> list = OpBasic::diference_edge(g, tree);
    std::vector<int>::iterator it;
    int factor = 1;

    it = list.begin();
    while(it != list.end()){
        int v = *it;
        int u = *(it+1);
        int d = OpBasic::distance(tree, v, u);
        if(factor < d){
            factor = d;
        }
        it = it + 2;
    }

    return factor;
}
