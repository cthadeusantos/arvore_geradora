#include "codigo/graph.hpp"
#include "codigo/frontier.hpp"
#include "codigo/opBasic.hpp"
#include "codigo/strech.hpp"
#include <iostream>
#include <ctime>


int total_arv = 0;

int main(int argc, char const *argv[])
{
    clock_t tStart = clock();
    if(argc < 3){
        std::cerr << "digite: " << argv[0] << " <path/nome_arq_in.txt> " << " <path/nome_arq_put.txt> " << std::endl;
        exit(-1);
    }
    Frontier f(argv[1], argv[2]);
    Strech s;
    Graph g;
    OpBasic op;

    f.read(g);

    f.printAdjList(g, "grafo de entrada", std::cout);
    f.printAdjMat(g, "grafo de entrada", std::cout);

    s.find_index(g);

    f.printAdjMat(g, "Grafo original", f.getOut());
    f.print(s.getIndex(), "\tindex = ", f.getOut());
    f.print(op.girth(g)-1, "\tlimite inferior = ", f.getOut());
    f.print(op.min_diameter_tree_value(g), "\tlimite superior = ", f.getOut());
    f.printAdjMat(s.getTree(), "arvore encontrada", f.getOut() );
    f.print(total_arv, "Total de arvores = ", f.getOut());

    //std::vector<int> c = op.centers(g);
    //std::vector<std::vector<int> > v(g.getQtdVertices(), std::vector<int>());

    /* Do your stuff here */
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    return 0;
}
