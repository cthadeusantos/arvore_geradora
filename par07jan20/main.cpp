#include "codigo/graph.hpp"
#include "codigo/frontier.hpp"
#include "codigo/opBasic.hpp"
#include "codigo/strech.hpp"
#include <iostream>
#include <ctime>

int main(int argc, char const *argv[])
{
    if(argc < 3){
        std::cerr << "digite: " << argv[0] << " <path/nome_arq_in.txt> " << " <path/nome_arq_put.txt> " << std::endl;
        exit(-1);
    }
    Frontier f(argv[1], argv[2]);
    Strech s;
    Graph g;
    OpBasic op;

    time_t time_begin, time_end;

    f.read(g);

    f.printAdjList(g, "grafo de entrada", std::cout);
    f.printAdjMat(g, "grafo de entrada", std::cout);

    time(&time_begin);
    s.find_index(g);
    time(&time_end);

    //s.find_index_thread(g);

    f.printAdjMat(g, "Grafo original", f.getOut());
    f.print(s.getIndex(), "\tindex = ", f.getOut());
    f.print(op.girth(g)-1, "\tlimite inferior = ", f.getOut());
    f.print(op.min_diameter_tree_value(g), "\tlimite superior = ", f.getOut());
    f.printAdjMat(s.getTree(), "arvore encontrada", f.getOut() );

    f.print(s.getTotalTree(), "total de arvores = ", f.getOut());
    f.print(difftime(time_end, time_begin), "tempo em seg: ", f.getOut());
    return 0;
}
