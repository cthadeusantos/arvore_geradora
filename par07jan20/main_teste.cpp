#include "codigo/graph.hpp"
#include "codigo/frontier.hpp"
#include "codigo/opBasic.hpp"
//#include "codigo/strech.hpp"
#include <iostream>
#include <ctime>
//#include <cmath> // floor

#include <thread>
#include <mutex>
#include <semaphore.h>

int index_global =  INF_VALUE;
int total_arv = 0;
Graph tree_global;
std::mutex mtx;
sem_t semaforo;

void find_index_pararell(Graph& g, int raiz, int start, int end, const int id);
void create_threads(Graph& g, int raiz, int qtd_core);
int find_factor(Graph& g, Graph& tree);
int vertice_maior_grau(Graph& g);

void create_threads_2(Graph& g);
int adj_id(Graph& g, int v, int adj);
int next(int a, int limite);


int main(int argc, char const *argv[])
{
    
    Frontier f;

    // std::ifstream in;
    // std::ofstream out;
    
    std::vector<Graph> vetor_g;
    std::vector<std::string> nomes;
    //Graph vetor_g[3];
    std::string dict("potencia_ciclo/");
    std::string name("potent_");
    Graph aux;
    int ciclo = 15;
    int i=0;
    //Graph g;
    while(ciclo < 16){
        int potencia = 2;
        std::string name2(name + std::to_string(ciclo) + "_");
        while(potencia < 3 /*ciclo/2*/){
            std::string name3(name2 + std::to_string(potencia) + ".txt");
            std::cout << name3 << std::endl;
            nomes.push_back(name3);
            //in.open(name3);
            f.open_in(dict + name3);
            ++i;
            f.read(aux);

            vetor_g.push_back(aux);
            //f.printAdjList(aux, "arv", std::cout);
            //in.close();
            f.close_in();
            ++potencia;
            aux.clear();
        }
        ++ciclo;
    }

    int id = 1;
    int raiz;
    int qtd_core;
    time_t time_begin, time_end;
    std::string saida("potencia_ciclo_s/");
    std::vector<std::string>::iterator it = nomes.begin();

    sem_init(&semaforo, 0, 4);

    std::ofstream resumo;
    resumo.open("potencia_ciclo_s/resumo_potent.txt", std::ios::out | std::ios::app);
    for(Graph g : vetor_g){
        raiz = vertice_maior_grau(g);
        qtd_core = g.grau(raiz);
        std::cout << "calculando o grafo " << *it << std::endl;

        time(&time_begin);
        //create_threads(g, raiz, qtd_core);
        create_threads_2(g);
        time(&time_end);

        int limit_inf = OpBasic::girth(g)-1;
        int limit_sup = OpBasic::min_diameter_tree_value(g);
        double tempo = difftime(time_end, time_begin)/60;

        f.open_out(saida + "saida_" + *it);
        f.printAdjMat(g, "Grafo original", f.getOut());
        f.print(index_global, "\tindex = ", f.getOut());
        f.print(limit_inf, "\tlimite inferior = ", f.getOut());
        f.print(limit_sup, "\tlimite superior = ", f.getOut());
        f.printAdjMat(tree_global, "arvore encontrada: ", f.getOut() );
        f.print(total_arv, "Total de arvores = ", f.getOut());
        f.print(difftime(time_end, time_begin), "tempo em seg: ", f.getOut());
        f.print(tempo ,"tempo em minutos: ", f.getOut() );

        resumo << g.getQtdVertices()<<" ; "<<g.grau(0)/2<<" ; "<< index_global <<" ; "<<limit_inf<<" ; "<<limit_sup<<" ; "<<tempo<<std::endl;

        f.close_out();
        ++it;

        index_global = INF_VALUE;
        tree_global.clear();
        total_arv = 0;
    }
    
    resumo.close();

    return 0;
}


void create_threads(Graph& g, int raiz, int qtd_core)
{
    std::thread vetor_th[qtd_core];
    int vetor_adj = g.adjList(raiz).size();

    int resto = vetor_adj % qtd_core;
    int passo = vetor_adj / qtd_core;
    int i = 0; // percorre o 'vetor_th'
    int j = 0; // percorre o 'vetor_adj'
    int th_id = 1; // debug pessoal

    while( resto > 0){
        vetor_th[i] = std::thread(find_index_pararell, std::ref(g), raiz, j, j+passo+1, th_id);
        ++i;
        j += passo+1;
        ++th_id;
        --resto;
    }

    while( i < qtd_core && j < vetor_adj ){
        vetor_th[i] = std::thread(find_index_pararell, std::ref(g), raiz, j, j+passo, th_id);
        ++i;
        j += passo;
        ++th_id;
    }

    for(int i=0; i < qtd_core; ++i){
        if( vetor_th[i].joinable()) vetor_th[i].join();
    }
}

void find_index_pararell(Graph& g, int raiz, int start, int end, const int id)
{
    sem_wait(&semaforo);

    int prox_vizinho[g.getQtdVertices()];
    int ult_colocado[g.getQtdVertices()];
    int v = raiz;
    int u;
    int arv = 0; // debug
    int index_local = INF_VALUE;
    Graph tree_local;
    //std::vector<Graph> vt;

    Frontier front;

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
                        int f = find_factor(g, tree);
                        ++arv;
                        
                        //vt.push_back(tree);
                        // LOCK
                        //mtx.lock(); 
                        if(f < index_local){
                            index_local = f;
                            tree_local = tree;
                            
                        }
                        //mtx.unlock();
                        // UN_LOCK
                    }else{
                        v = g.next_vertex(v);
                        continue;
                    }
                }
                tree.remove_aresta(v, u);  
            }
        }
    }
    mtx.lock();
    std::cout << "thread " << id << " criou " << arv << " arvores." << std::endl;
    
    int i = 1;
    //std::cout << "raiz: " << raiz << std::endl;
    //std::cout << "start: " << start << std::endl;
    /*
    std::cout << "end: " << end << std::endl;
    for(auto g : vt){
        front.printAdjList(g, "arv "+std::to_string(i), std::cout);
        ++i;
    }
    */
    total_arv += arv;
    index_global = index_local;
    tree_global = tree_local;
    mtx.unlock();

    sem_post(&semaforo);
}


int find_factor(Graph& g, Graph& tree)
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

void create_threads_2(Graph& g)
{
    std::cout << "ENTROU THREAD 2" << std::endl;
    int raiz = vertice_maior_grau(g);
    int qtd = g.grau(raiz);
    int id=0;

    std::thread vetor_th[qtd];

    if(g.possui_aresta(raiz, g.ant_vertex(raiz) ) ){
        id = adj_id(g, raiz, g.ant_vertex(raiz) );
        //std::cout << "raiz = " << raiz << ", id = " << id << std::endl;
    }

    for(int i=0; i < qtd; ++i){
        vetor_th[i] = std::thread(find_index_pararell, std::ref(g), raiz, id, id+1, i);
        id = next(id, qtd);
    }

    for(int i=0; i < qtd; ++i){
        vetor_th[i].join();
    }
}


int next(int a, int limite)
{
    ++a;
    return a == limite ? 0 : a;
}

int vertice_maior_grau(Graph& g)
{
    int raiz = -1;
    int maior_grau = -1;
    for(int i=0; i < g.getQtdVertices(); ++i){
        if(g.grau(i) > maior_grau){
            raiz = i;
            maior_grau = g.grau(i);
        }
    }
    return raiz;
}

int adj_id(Graph& g, int v, int adj)
{
    int id=0;
    for(int u : g.adjList(v) ){
        if(u == adj){
            break;
        }
        ++id;
    }
    return id;
}
