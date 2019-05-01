//Main file

#include <iostream>
#include "graph.hpp"

using std::cout;


int main([[maybe_unused]]int argc, [[maybe_unused]] char* argv[])
{
    graph_lib::graph<char, true> g{};  

    std::cout << "It works \n";
    return 0;
}