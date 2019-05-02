#include <gtest/gtest.h>
#include "graph_lib_base.hpp"
#include "graph_algorithms.hpp"

// included only in case some debug lines are needed
#include <iostream>

TEST(algorithms, find_all_connected_vertices_of_the_same_degree)
{
    graph_lib::graph<char> g{std::vector { std::pair{'A', std::vector{'B','C'} },
                                           std::pair{'B', std::vector{'A','C'} },
                                           std::pair{'C', std::vector{'A','B'} } 
                                         }
                            };

    std::vector vec{ std::pair{'A','B'}, std::pair{'A','C'},
                     std::pair{'B','A'}, std::pair{'B','C'},
                     std::pair{'C','A'}, std::pair{'C','B'} };

    auto const results = graph_lib::find_all_connected_vertices_of_the_same_degree(g,2);

    ASSERT_EQ(results, vec);
}

TEST(algorithms, find_triangular_faces)
{
    graph_lib::graph<char> g{std::vector { std::pair{'A', std::vector{'B','C'} },
                                           std::pair{'B', std::vector{'A','C'} },
                                           std::pair{'C', std::vector{'A','B'} } 
                                         }
                            };

    std::vector vec { std::tuple{'A','B','C'}};

    auto results = graph_lib::find_triangular_faces(g);

    ASSERT_EQ(results, vec);
}