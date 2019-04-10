#pragma once

/*  
    Class for represntation of the graph, used to represnt polyhedron.
    For the reperesentation of graph vector of edges is used.
    For the representation of edgdes std::pair<char,char> is used.
    Following functionalities are provided:
    
    num_vertices()           Return the number of vertices in G
    num_edges()              Return the number of edges in G
    vertices()               Return an iterator of the vertices of G
    edges()                  Return an iterator of the edges of G

    degree(v)                Return the degree of v
    adjacent_vertices(v)     Return an iterator of the vertices adjacent to v
    incident_edges(v)        Return an iterator of the edges incident upon v
    opposite(v,e)            Return the endpoint of edge e distinct from v
    are_adjacent(v,w)        Return whether vertices v and w are adjacent 

    insert_edge(v,w)         Insert and return an undirected edge between vertices v and w
    insert_vertex(v)         Insert and return a new (isolated) numbering
                             vertex v storing the object o at this position 
    remove_vertex(v)         Remove vertex v and all its incident edges 
    remove_edge(e)           Remove edge 
*/


#include "graph_lib_base.h"
#include <vector>
#include <algorithm>
#include <assert.h>

template <typename V>
class graph_lib::graph
{
private:
    std::vector<std::pair <V, std::vector<V>>> _adjacency_list;
    typename std::vector<V>::size_type         _number_of_edges;

public:
    //rule of five
    explicit graph() = default;
    explicit graph(const graph&) = default;
    explicit graph(graph&&) = default;

    graph& operator=(const graph&) = default;
    graph& operator=(graph&&) = default;

    virtual ~graph() = default;

    [[nodiscard]] constexpr auto num_vertices() const noexcept -> std::vector<std::pair <V, std::vector<V>>>::size_type
    {
        return _adjacency_list.size();
    }

    [[nodiscard]] constexpr auto num_edges() const noexcept -> std::vector<V>::size_type
    {
        return _number_of_edges;
    }

    // all of the required iterators
    [[nodiscard]] auto begin() noexcept 
    {
        return std::begin(_adjacency_list);
    }

    [[nodiscard]] auto const cbegin() const noexcept
    {
        return std::cbegin(_adjacency_list);
    }

    [[nodiscard]] auto end() noexcept
    {
        return std::end(_adjacency_list);
    }

    [[nodiscard]] auto const cend() const noexcept
    {
        return std::end(_adjacency_list);
    }

    [[nodiscard]] auto rbegin() noexcept
    {
        return std::rbegin(_adjacency_list);
    }

    [[nodiscard]] auto const crbegin() const noexcept
    {
        return std::crbegin(_adjacency_list);
    }

    [[nodiscard]] auto rend() noexcept
    {
        return std::rend(_adjacency_list);
    }

    [[nodiscard]] auto const crend() const noexcept
    {
        return std::crend(_adjacency_list);
    }

    [[nodiscard]] constexpr auto degree(V vertex) const noexcept
    {
        auto const & it = std::find(std::begin(_adjacency_list), std::end(_adjacency_list),
                                                [&](auto const & i){ return i.first == vertex;});
        assert(it != std::cend(_adjacency_list));

        return it->second.size();
    }
};
