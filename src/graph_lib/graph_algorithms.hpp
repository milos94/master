#include "graph_lib_base.hpp"
#include "graph.hpp"
#include <utility>
#include <tuple>


/*

Let L be an initially empty list;
for each vertex v in G.vertices()
{
    if ( G.degree(v) == d) then
        for each vertex u in G.adjacentVertices(v)
        {
            if (G.degree(u) == d) then
                L.insertLast ((v,u));// insert edge (v,u) into L
        }
}

*/

template <typename V, bool undirected>
auto graph_lib::find_all_connected_vertices_of_the_same_degree(graph_lib::graph<V,undirected> const & g,
                                                               typename graph_lib::graph<V,undirected>::edges_size_type const & degree)
    -> typename std::vector<std::pair<V,V>>
{
    std::vector<std::pair<V,V>> ret_val{};
    ret_val.reserve(g.num_edges());

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

/*

Let Q be an initially empty priority queue;
for each vertex v in G.vertices() {
    Q.insertItem (G.degree(v), v); // insert a vertex v with degree of v as key into Q
}

NOTE: instead of priority queue (std::priority_queue) std::vecotor is used
    Priority queu has const time complexity for finding min element but insert is logn
        Creating a priority queue of n elements would than take O(nlogn)
    Vector has cosnt time time complexity for inserting elements
        If vecotor is sorted, which takes O(nlogn) than min element is the first element and finding it is cosnt time
    Becaues of this and vector's simpler interface, vector is used.
*/

template <typename V, bool undirected>
auto graph_lib::find_orders_of_vertices(graph<V,undirected> const & g)
    -> typename std::vector<std::pair<V, typename graph<V,undirected>::edges_size_type>>
{
    std::vector<std::pair<V, typename graph<V,undirected>::edges_size_type>> vec{};
    vec.reserve(g.num_vertices());

    for (auto it = g.cbegin(); it != g.cend(); ++it)
    {
        vec.emplace_back(std::pair{it->first, std::size(it->second)});
    }

    std::sort(std::begin(vec), std::end(vec), [](auto const & first, auto const & secod)
                                                {return first.second < secod.second;});

    return vec;
}