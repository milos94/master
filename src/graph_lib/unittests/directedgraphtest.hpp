#include <gtest/gtest.h>
#include "graph.hpp"

TEST(directed_graph, insert_vetex)
{
    graph_lib::graph<char, false> g{};
    ASSERT_EQ(0, g.num_vertices());
    g.insert_vertex('A');
    ASSERT_EQ(1, g.num_vertices());

    g.insert_vertex('B');
    g.insert_vertex('C');
    ASSERT_EQ(3, g.num_vertices());

    ASSERT_DEATH(g.insert_vertex('A'), "Assertion `\\(it == std::c?end\\(_adjacency_list\\)\\) != flag' failed.");
}

TEST(directed_graph, insert_edge)
{
    graph_lib::graph<char, false> g{};
    ASSERT_EQ(0, g.num_vertices());
    g.insert_vertex('A');
    ASSERT_EQ(1, g.num_vertices());

    g.insert_vertex('B');
    g.insert_vertex('C');
    ASSERT_EQ(3, g.num_vertices());

    ASSERT_EQ(0, g.num_edges());

    g.insert_edge('A', 'B');
    ASSERT_EQ(1, g.num_edges());

    g.insert_edge('B', 'C');
    g.insert_edge('A', 'C');
    ASSERT_EQ(3, g.num_edges());

    g.insert_edge('B', 'A');
    ASSERT_EQ(4,g.num_edges());

    ASSERT_DEATH(g.insert_edge('A','B'), "Assertion `\\(it == std::c?end\\(node_a->second\\)\\) != flag' failed\\.");
    ASSERT_DEATH(g.insert_edge('A','G'), "Assertion `\\(it == std::c?end\\(_adjacency_list\\)\\) != flag' failed.");
}

TEST(directed_graph, remove_vertex)
{
    graph_lib::graph<char,false> g{};

    ASSERT_EQ(0, g.num_vertices());

    g.insert_vertex('A');
    g.insert_vertex('B');
    g.insert_vertex('C');

    ASSERT_EQ(3, g.num_vertices());

    g.remove_vertex('A');

    ASSERT_EQ(2, g.num_vertices());

    ASSERT_DEATH(g.remove_vertex('A'), "Assertion `\\(it == std::c?end\\(_adjacency_list\\)\\) != flag' failed.");
}

TEST(directed_graph, remove_edge)
{
    graph_lib::graph<char,false> g{};
    ASSERT_EQ(0, g.num_vertices());
    g.insert_vertex('A');
    ASSERT_EQ(1, g.num_vertices());

    g.insert_vertex('B');
    g.insert_vertex('C');
    ASSERT_EQ(3, g.num_vertices());

    ASSERT_EQ(0, g.num_edges());

    g.insert_edge('A', 'B');
    ASSERT_EQ(1, g.num_edges());

    g.insert_edge('B', 'C');
    g.insert_edge('A', 'C');
    ASSERT_EQ(3, g.num_edges());

    g.remove_edge('A', 'B');
    ASSERT_EQ(2, g.num_edges());

    ASSERT_DEATH(g.remove_edge('A', 'B'), "Assertion `\\(it == std::c?end\\(node_a->second\\)\\) != flag' failed\\.");
    ASSERT_DEATH(g.remove_edge('C', 'A'), "Assertion `\\(it == std::c?end\\(node_a->second\\)\\) != flag' failed\\.");
    ASSERT_DEATH(g.remove_edge('A', 'G'), "Assertion `\\(it == std::c?end\\(_adjacency_list\\)\\) != flag' failed.");
    
}

TEST(directed_graph, parameter_constructor)
{
    graph_lib::graph<char, false> g{std::vector { std::pair{'A', std::vector{'B','C'} },
                                           std::pair{'B', std::vector{'A','C'} },
                                           std::pair{'C', std::vector{'A','B'} } 
                                         }
                            };
    
    ASSERT_EQ(3, g.num_vertices());
    ASSERT_EQ(6, g.num_edges());
}

TEST(directed_graph, degree)
{
    graph_lib::graph<char,false> g{std::vector { std::pair{'A', std::vector{'B','C'} },
                                           std::pair{'B', std::vector{'A','C'} },
                                           std::pair{'C', std::vector{'A','B'} } 
                                         }
                            };
    
    ASSERT_EQ(3, g.num_vertices());
    ASSERT_EQ(6, g.num_edges());

    ASSERT_EQ(2, g.degree('A'));
    ASSERT_EQ(2, g.degree('B'));

    g.remove_edge('A', 'B');

    ASSERT_EQ(1, g.degree('A'));
    ASSERT_EQ(2, g.degree('B'));

    g.remove_vertex('C');

    ASSERT_EQ(0, g.degree('A'));
    ASSERT_DEATH((void)g.degree('C'), "Assertion `\\(it == std::c?end\\(_adjacency_list\\)\\) != flag' failed\\.");
}

TEST(directed_graph, adjacent_vertices)
{
    graph_lib::graph<char,false> g{std::vector { std::pair{'A', std::vector{'B','C'} },
                                                 std::pair{'B', std::vector{'A','C'} },
                                                 std::pair{'C', std::vector{'A','B'} } 
                                               }
                                  };
    
    ASSERT_EQ(3, g.num_vertices());
    ASSERT_EQ(6, g.num_edges());

    std::vector vec{'B','C'};

    ASSERT_EQ(vec, g.adjacent_vertices('A'));

    g.insert_vertex('D');

    g.insert_edge('A', 'D');

    vec.emplace_back('D');
    
    ASSERT_EQ(vec, g.adjacent_vertices('A'));
}

TEST(directed_graph, are_adjacent)
{
    graph_lib::graph<char,false> g{std::vector { std::pair{'A', std::vector{'B','C'} },
                                                 std::pair{'B', std::vector{'A','C'} },
                                                 std::pair{'C', std::vector{'A','B'} } 
                                               }
                                  };
    
    ASSERT_EQ(3, g.num_vertices());
    ASSERT_EQ(6, g.num_edges());

    ASSERT_EQ(true, g.are_adjacent('A', 'B'));
    ASSERT_EQ(true, g.are_adjacent('B', 'A'));
    ASSERT_EQ(true, g.are_adjacent('A', 'C'));
    ASSERT_EQ(true, g.are_adjacent('C', 'A'));

    g.remove_edge('A', 'B');

    ASSERT_EQ(false, g.are_adjacent('A', 'B'));
    ASSERT_EQ(true, g.are_adjacent('B', 'A'));

    g.remove_vertex('C');

    ASSERT_DEATH((void)g.are_adjacent('A','C'), "Assertion `\\(it == std::c?end\\(_adjacency_list\\)\\) != flag' failed\\.");
    ASSERT_DEATH((void)g.are_adjacent('C','A'), "Assertion `\\(it == std::c?end\\(_adjacency_list\\)\\) != flag' failed\\.");

    g.insert_vertex('E');
    g.insert_vertex('G');

    g.insert_edge('E','G');

    ASSERT_EQ(true, g.are_adjacent('E','G'));
    ASSERT_EQ(false, g.are_adjacent('G','E'));

}