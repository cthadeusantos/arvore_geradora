#include "codigo/graph.hpp"
#include "codigo/frontier.hpp"
#include "codigo/opBasic.hpp"
//#include "codigo/strech.hpp"
#include <iostream>
#include <ctime>

#include <thread>  // std::thread
#include <mutex>   // std::mutex
#include <semaphore.h> // sem_t, sem_init, sem_wait, sem_post, sem_destroy
#include <sstream> // std::stringstream

int index_global =  INF_VALUE;
int total_arv = 0;
Graph tree_global;


std::mutex mtx;
sem_t semaforo;

//static const std::string min("min");
//static const std::string max("max");


void find_index_pararell(Graph& g, int raiz, int start, int end, const int id);
// void create_threads(Graph& g, int raiz, int qtd_core);
void create_threads(Graph& g);
int find_factor(Graph& g, Graph& tree);
int vertice_maior_grau(Graph& g);

int adj_id(Graph& g, int v, int adj);
int next(int a, int limite);

int main(int argc, char const *argv[])
{
    if(argc != 4){
        std::cerr << "quantidade de parametros incorretos!!" << std::endl;
        std::cerr << "digite: " << argv[0] << " <path/nome_arq_in.txt> " << " <path/nome_arq_put.txt> " << "<'n' cores da maquina>(possivelmente é 4)" << std::endl;
        exit(-1);
    }

    std::string aux(argv[3]);
    for(char c : aux){
        if( not std::isdigit(c) ){
            std::cerr << "terceiro comando invalido!!\n\t\tdigite um numero inteiro." << std::endl;
            exit(-1);

        }
    }

    Frontier f(argv[1], argv[2]);
    OpBasic op;
    Graph g;

    //int raiz;



    int qtd_core;
    time_t time_begin, time_end;

    std::stringstream(aux) >> qtd_core;

    sem_init(&semaforo, 0, qtd_core);

    f.read(g);

    f.printAdjList(g, "grafo de entrada", std::cout);

    time(&time_begin); // inicia a contagem de tempo
    create_threads(g);
    time(&time_end);   // encerra a contagem de tempo

    f.printAdjMat(g, "Grafo original", f.getOut());
    f.print(index_global, "\tindex = ", f.getOut());
    f.print(op.girth(g)-1, "\tlimite inferior = ", f.getOut());
    f.print(op.min_diameter_tree_value(g), "\tlimite superior = ", f.getOut());
    f.printAdjMat(tree_global, "arvore encontrada: ", f.getOut() );

    f.print(total_arv, "Total de arvores = ", f.getOut());
    f.print(difftime(time_end, time_begin), "tempo em seg: ", f.getOut());
    f.print(difftime(time_end, time_begin)/60 ,"tempo em minutos: ", f.getOut() );

    sem_destroy(&semaforo);

    return 0;
}
/*
void create_threads(Graph& g, int raiz, int qtd_core)
{
    //std::thread vetor_th[qtd_core];
    std::vector<std::thread> vetor_th;
    //std::queue<int> start;
    //std::queue<int> end;
    int vetor_adj = g.adjList(raiz).size();

    int resto = vetor_adj % qtd_core;
    int passo = vetor_adj / qtd_core;
    int qtd_th = 0; // percorre o 'vetor_th'
    int j = 0; // percorre o 'vetor_adj'
    int th_id = 1; // debug pessoal

    while( resto > 0){
        //vetor_th[i] = std::thread(find_index_pararell, std::ref(g), raiz, j, j+passo+1, th_id);
        vetor_th.push_back(std::thread(find_index_pararell, std::ref(g), raiz, j, j+passo+1, th_id));
        //start.push(j);
        //end.push(j+passo+1);
        ++qtd_th;
        j += passo+1;
        ++th_id;
        --resto;
    }

    while( qtd_th < qtd_core && j < vetor_adj ){
        //vetor_th[i] = std::thread(find_index_pararell, std::ref(g), raiz, j, j+passo, th_id);
        vetor_th.push_back(std::thread(find_index_pararell, std::ref(g), raiz, j, j+passo, th_id));
        //start.push(j);
        //end.push(j+passo+1);
        ++qtd_th;
        j += passo;
        ++th_id;
    }

    for(int i=0; i < qtd_core; ++i){
        vetor_th[i].join();
    }


}
*/

void find_index_pararell(Graph& g, int raiz, int start, int end, const int id)
{

    sem_wait(&semaforo); // Apenas 4 threads puderam fazer este código por vez

    int prox_vizinho[g.getQtdVertices()];
    int ult_colocado[g.getQtdVertices()];
    int v = raiz;
    int u;
    int arv = 0; // debug
    int index_local = INF_VALUE;
    Graph tree_local;

    int grt;

    Frontier front;

    Graph tree(g.getQtdVertices());

    OpBasic op;
    //int raiz;

    grt = op.girth(g); // alteracao LF

    for(int i=0; i < g.getQtdVertices(); ++i){
        prox_vizinho[i] = 0;
        ult_colocado[i] = -1;
    }

    prox_vizinho[v] = start;

    while(index_global > grt-1 ){
        if(v == raiz){
            if(prox_vizinho[v] == end){
                break; // Fim do algoritmo
            }
        }

        if( prox_vizinho[v] == g.grau(v) ){
            prox_vizinho[v] = 0;
            v = g.ant_vertex(v);
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
                        if(f < index_local){
                            index_local = f;
                            tree_local = tree;
                            if(index_local == grt-1){// alteracao LF
                              break;// alteracao LF
                            }// alteracao LF

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
    mtx.lock();
    std::cout << "thread " << id << " criou " << arv << " arvores." << std::endl;

    if(index_local < index_global) {
      total_arv += arv;
      index_global = index_local;
      tree_global = tree_local;
    }
    mtx.unlock();

    sem_post(&semaforo); // a thread libera espaço para a proxima
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

void create_threads(Graph& g)
{
    int raiz = vertice_maior_grau(g);
    int qtd = g.grau(raiz);
    int id=0;

    std::thread vetor_th[qtd];

    if(g.possui_aresta(raiz, g.ant_vertex(raiz) ) ){
        id = adj_id(g, raiz, g.ant_vertex(raiz) );
    }

    for(int i=0; i < qtd; ++i){
        vetor_th[i] = std::thread(find_index_pararell, std::ref(g), raiz, id, id+1, i);
        id = next(id, qtd);
    }

    // std::cout << "bye";

    for(int i=0; i < qtd; ++i){
        vetor_th[i].join();
    }
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

int next(int a, int limite)
{
    ++a;
    return a == limite ? 0 : a;
}
