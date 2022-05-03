#include "strech.hpp"
#include "opBasic.hpp"
#include "frontier.hpp"

void Strech::find_index(Graph& g)
{
    int prox_vizinho[g.getQtdVertices()];
    int ult_colocado[g.getQtdVertices()];
    int v = 0;
    int u;
    int grt;

    OpBasic op; // alteracao LF
    //int index = g.getQtdVertices();
    // int arv = 0;
    index = INF_VALUE; //g.getQtdVertices();

    Graph tree(g.getQtdVertices());
    grt = op.girth(g); // alteracao LF

    for(int i=0; i < g.getQtdVertices(); ++i){
        prox_vizinho[i] = 0;
        ult_colocado[i] = -1;
    }

    while( v >= 0 ){
        if( prox_vizinho[v] == g.grau(v) ){
            prox_vizinho[v] = 0;
            --v;
            if(v < 0) break;
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
