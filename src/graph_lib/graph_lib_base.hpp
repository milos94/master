#pragma once
/*  This is only used to declare all of the classes in one namespace
    
*/

namespace graph_lib{
    template <typename V, bool undirected = true>
    class graph;
    
    template <typename V, bool undirected> 
    void sort_graph_by_degree(graph<V,undirected> & g);

    template <typename V, bool undirected>
    auto find_all_connected_vertices_of_the_same_degree(graph<V,undirected> & g)
        -> typename graph<V,undirected>::node_type;
}