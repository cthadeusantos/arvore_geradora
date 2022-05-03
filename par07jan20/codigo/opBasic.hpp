#ifndef OP_BASIC_HPP_
#define OP_BASIC_HPP_

#include "graph.hpp"
//#include <tuple>
#include <vector>
#include <limits>
#include <stack> // pilha
#include <queue> // fila

#define INF_VALUE std::numeric_limits<int>::max()
#define INF "inf"

class OpBasic
{
private:
    static bool cyclic(Graph& g, int v);
    static void clear(std::queue<int>& q);
    static void clear(std::stack<int>& s);
    static bool pertence(int x, std::vector<int>& v);
    static std::vector<int> short_path(Graph& g, int v, int u);
public:
    OpBasic() { }
    ~OpBasic() { }

    static bool is_cyclic(Graph& g);
    static bool is_tree(Graph& g);
    static std::vector<int> diference_edge(Graph& g, Graph& t);
    static int distance(Graph& g, int v, int u);
    static int girth(Graph& g);
    static std::vector<int> centers(Graph& g);
    static int diameter(Graph& g);
    static std::vector<std::vector<int> > distance(Graph& g, int v);
    static int min_diameter_tree_value(Graph& g);
};

#endif