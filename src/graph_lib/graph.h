#pragma once

/*  
    Class for represntation of the graph, used to represnt polyhedron.
    For the reperesentation of graph vector of edges is used.
    For the representation of edgdes std::pair<char,char> is used.
    Following functionalities are provided:
    
    numVertices()           Return the number of vertices in G
    numEdges()              Return the number of edges in G
    vertices():             Return an iterator of the vertices of G
    edges()                 Return an iterator of the edges of 

    degree(v)               Return the degree of v
    adjacentVertices(v)     Return  an  iterator  of  the  vertices  adjacent to v
    incidentEdges(v)        Return   an   iterator   of   the   edges   incident upon v
    opposite(v,e)           Return the endpoint of edge e distinct from v
    areAdjacent(v,w)        Return whether vertices v and w are adjacent 

    insertEdge(v,w)         Insert  and  return  an  undirected  edge between vertices v and w
    insertVertex(v)         Insert and return a new (isolated) numbering
                            vertex v storing the object o at this position 
    removeVertex(v)         Remove vertex v and all its incident edges 
    removeEdge(e)           Remove edge    
*/


#include "graph_lib.h"
#include <vector>

using graph_lib::graph;
using vector = std::vector<std::pair<char,char>>;

class graph
{

private:
    vector edges;

public:
    //rule of five
    explicit graph() = default;
    explicit graph(const graph&) = default;
    explicit graph(graph&&) = default;

    graph& operator=(const graph&) = default;
    graph& operator=(graph&&) = default;

    virtual ~graph();

};
