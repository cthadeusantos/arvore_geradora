#ifndef FRONTIER_HPP_
#define FRONTIER_HPP_

#include "graph.hpp"
#include "strech.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

#define INF_VALUE std::numeric_limits<int>::max()
#define INF "inf"

class Frontier
{
private:
    std::ifstream in;
    std::ofstream out;

    bool is_inf(int value);
public:
    Frontier(const char* name_in, const char* name_out);
    Frontier(){};
    ~Frontier();

    std::ostream& getOut() { return this->out; }

    void printAdjList(Graph g,std::string msg, std::ostream& out=std::cout);
    void printAdjMat(Graph g,std::string msg, std::ostream& out=std::cout);
    void print(Strech& s);
    void print(std::vector<int> vetor, std::string str="",std::ostream& out=std::cout);
    void print(int value, std::string str="", std::ostream& out=std::cout);
    void read(Graph& g);

    void msg_error(const std::string& msg);
};

#endif