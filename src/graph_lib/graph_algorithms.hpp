#include "graph_lib_base.hpp"
#include "graph.hpp"
#include <utility>
#include <tuple>

template <typename V, bool undirected>
auto graph_lib::find_all_connected_vertices_of_the_same_degree(graph_lib::graph<V,undirected> const & g,
                                                               typename graph_lib::graph<V,undirected>::edges_size_type const & degree)
    -> typename std::vector<std::pair<V,V>>
{
    std::vector<std::pair<V,V>> ret_val{};
    ret_val.reserve(g.num_edges());

    //TODO: fix it so ranged for works with const iterators
    //for (auto const & [vertex, edges] : std::as_const(g))
    for (auto it = g.cbegin(); it != g.cend(); ++it)
    {
        auto const & [vertex, edges] = *it;
        if(g.degree(vertex) == degree)
        {
            for (auto const & adjacent_vertex : std::as_const(edges))
            {
                if(g.degree(adjacent_vertex) == degree)
                {
                    ret_val.emplace_back(std::pair{vertex, adjacent_vertex});
                }
            }
        }
    }
    return ret_val;
}

/*
Pseudo code for the triangular face finding algorithm

for each vertex u in G.vertices() {
    for each edge e in G.incidentEdges(u)
    {
        v = G.opposite (u,e); // return the endpoint of edge e distinct from u
        for each vertex w in G.adjacentVertex(u)
        {
            if G.areAdjacent(v,w) then
                T.InsertLast((u,v,w)); // insert a new triple (u, v, w) into list T
        }
        G.removeEdge((u,v)); //remove edge (u,v) from G
    }
}
return T

*/
template <typename V, bool undirected>
auto graph_lib::find_triangular_faces(graph_lib::graph<V,undirected> const & g)
        -> typename std::vector<std::tuple<V,V,V>>
{
    std::vector<std::tuple<V,V,V>> ret_val{};
    graph_lib::graph<V, undirected> temp{g};

    for (auto & [u, edges] : temp)
    {
        for (size_t i = 0; i< std::size(edges); ++i)
        {
            auto v = edges.at(i);

            for (auto & w : g.adjacent_vertices(u))
            {
                // since graph reprezents a polyhedron there will be no vertices connnected to themself
                if(temp.are_adjacent(v,w))
                {
                    ret_val.emplace_back(std::tuple{u, v, w});
                }
            }
            temp.remove_edge(u, v);
        }
    }
    return ret_val;
}

/*
Pesudo code for cone triangulation

Let S be an initially empty list;
for each triple (u,v,w) in T.elements() {
    if not ( (u == q) or (v == q) or (w == q) ) then
        S.InsertLast((q,u,v,w)); // Insert a new tetrahedron (q,u,v,w) into list S
    }
return S
*/
template <typename V>
auto graph_lib::cone_triangulation(std::vector<std::tuple<V,V,V>> const & T, V q)
        -> typename std::vector<std::tuple<V,V,V,V>>
{
    std::vector<std::tuple<V,V,V,V>> ret_val{};

    for(auto const & [u, v, w] : T)
    {
        if((u != q) && (v != q) && (w != q))
        {
            ret_val.emplace_back(std::tuple{q, u, v, w});
        }
    }

    return ret_val;
}

template <typename V, bool undirected>
std::ostream & operator<<(std::ostream & ost, graph_lib::graph<V,undirected> const & g)
{
    for (auto it = g.cbegin(); it != g.cend(); ++it)
    {
        ost << "Vertex: " << it->first << " is connected to: ";
        for (auto const & edge : std::as_const(it->second))
        {
            ost << edge << ", ";
        }
        ost << ";\n";
    }

    return ost;
}