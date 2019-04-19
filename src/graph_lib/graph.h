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
#include <string>
#include <algorithm>
#include <type_traits>
#include <assert.h>

template <typename V, bool undirected>
class graph_lib::graph
{
private:

    using node_type = std::conditional_t
                            < std::is_same_v < std::decay<V>, char * >,
                              std::string,
                              V >;

    std::vector<std::pair <node_type, std::vector<node_type>>> _adjacency_list;
    typename std::vector<node_type>::size_type                 _number_of_edges;

public:
    //rule of five
    explicit graph() = default;
    explicit graph(const graph&) = default;
    explicit graph(graph&&) = default;

    graph& operator=(const graph&) = default;
    graph& operator=(graph&&) = default;

    virtual ~graph() = default;

    // returns the number of vertices in G
    [[nodiscard]] constexpr auto num_vertices() const noexcept 
        -> typename std::vector< std::pair < node_type, std::vector<node_type> > >::size_type
    {
        return _adjacency_list.size();
    }

    // returns the number of edges in G
    [[nodiscard]] constexpr auto num_edges() const noexcept 
        -> typename std::vector<node_type>::size_type
    {
        return _number_of_edges;
    }

    // all of the required iterators
    // by default you iterate trough the std::pair<V, std::vector<V>> where v is the vertex and vector contains all of the adjacent vertices to v
    #pragma region iterators
    [[nodiscard]] auto begin() noexcept (noexcept (std::begin(_adjacency_list) ) )  
        -> typename std::vector< std::pair < node_type, std::vector<node_type> > >::iterator
    {
        return std::begin(_adjacency_list);
    }

    [[nodiscard]] auto const cbegin() const noexcept (noexcept (std::cbegin(_adjacency_list) ) ) 
        -> typename std::vector< std::pair < node_type, std::vector<node_type> > >::const_iterator
    {
        return std::cbegin(_adjacency_list);
    }

    [[nodiscard]] auto end() noexcept (noexcept (std::end(_adjacency_list) ) )
        -> typename std::vector< std::pair <node_type, std::vector<node_type> > >::iterator
    {
        return std::end(_adjacency_list);
    }

    [[nodiscard]] auto const cend() const noexcept (noexcept (std::cend(_adjacency_list) ) )
        -> typename std::vector< std::pair < node_type, std::vector<node_type> > >::const_iterator
    {
        return std::cend(_adjacency_list);
    }

    [[nodiscard]] auto rbegin() noexcept (noexcept (std::rbegin(_adjacency_list) ) )
        -> typename std::vector< std::pair < node_type, std::vector<node_type> > >::reverse_iterator
    {
        return std::rbegin(_adjacency_list);
    }

    [[nodiscard]] auto const crbegin() const noexcept (noexcept (std::crbegin(_adjacency_list) ) )
        -> typename std::vector< std::pair < node_type, std::vector<node_type> > >::const_reverse_iterator
    {
        return std::crbegin(_adjacency_list);
    }

    [[nodiscard]] auto rend() noexcept (noexcept (std::rend(_adjacency_list) ) )
        -> typename std::vector< std::pair < node_type, std::vector<node_type> > >::reverse_iterator
    {
        return std::rend(_adjacency_list);
    }

    [[nodiscard]] auto const crend() const noexcept (noexcept (std::crend(_adjacency_list) ) ) 
        -> typename std::vector< std::pair < node_type, std::vector<node_type> > >::const_reverse_iterator
    {
        return std::crend(_adjacency_list);
    }
    #pragma endregion
    
    // returns the degree of the vertex
    // assets whether the graph contains that vertex
    [[nodiscard]] constexpr auto degree(V vertex) const 
        -> typename std::vector<node_type>::size_type
    {
        auto const & it = std::find(std::begin(_adjacency_list), std::end(_adjacency_list),
                                                [&](auto const & i){ return i.first == vertex;});
        assert(it != std::cend(_adjacency_list));

        return it->second.size();
    }

    // returns the vector of adjacent verices of the vertex
    // assets whether the graph contains that vertex
    [[nodiscard]] constexpr decltype(auto) adjacent_vertices(V vertex) const
        -> typename std::vector<node_type> const &
    {
        auto const & it = std::find(std::begin(_adjacency_list), std::end(_adjacency_list),
                                                [&](auto const & i){ return i.first == vertex;});
        assert(it != std::cend(_adjacency_list));

        return it->second;
    }

    // insertns new vertex into the graph
    // first check if graph already contains new vertex
    void insert_vertex(V vertex) 
    {
        auto const & it = std::find(std::begin(_adjacency_list), std::end(_adjacency_list),
                                                [&](auto const & i){ return i.first == vertex;});
        assert(it == std::cend(_adjacency_list));

        _adjacency_list.emplace_back(std::make_pair< node_type, std::vector<node_type> >(vertex, std::vector<node_type>{}) );
    }

};
