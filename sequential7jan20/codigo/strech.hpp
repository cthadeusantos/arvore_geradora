#ifndef STRECH_HPP_
#define STRECH_HPP_

#include "graph.hpp"

class Strech
{
private:
    int index;
    Graph tree;
public:
    Strech() { index = -1; tree = Graph(); }
    ~Strech() { }

    void find_index(Graph& g);

    int find_factor(Graph& g, Graph& tree);

    int getIndex(){ return index; }
    Graph getTree(){ return tree; }
};

#endif
