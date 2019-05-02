#pragma once
#include <vector>
/*  This is only used to declare all of the classes in one namespace
    
*/

namespace graph_lib{
    template <typename V, bool undirected = true>
    class graph;

    template <typename V, bool undirected>
    auto find_all_connected_vertices_of_the_same_degree(graph<V,undirected> const & g,
                                                        typename graph<V,undirected>::size_type const & order)
        -> typename std::vector<std::pair<V,V>>;
    
    template <typename V, bool undirected>
    auto find_triangular_faces(graph<V,undirected> const & g)
        -> typename std::vector<std::tuple<V,V,V>>;
    
    template <typename V>
    auto cone_triangulation(std::vector<std::tuple<V,V,V>> const & T, V vertex)
        -> typename std::vector<std::tuple<V,V,V,V>>;

}