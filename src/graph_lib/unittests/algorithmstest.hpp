#include <gtest/gtest.h>
#include "graph_lib_base.hpp"
#include "graph_algorithms.hpp"

// included only in case some debug lines are needed
#include <iostream>
#include <string>

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

/*
  A1, A2, A3, A4, A5, B1, B2, B3, B4, B5, C1,  C2,  C3,  C4
  and  edgese  in  corresponding:  
  A1A2,  A1A5,  A1B1,  A1C1, A1C4,  
  A2A3,  A2B1,  A2B2,  A2C3, A2C4,
  A3A4,  A3B2,  A3B3,  A3C2, A3C3,
  A4A5,  A4B3,  A4B4,  A4C1, A4C2,  
  A5B1,  A5B4,  A5C1,
  B1B2,  B1B4,  B1B5,  
  B2B3,  B2B5,  
  B3B4,  B3B5,  
  B4B5, 
  C1C2,  C1C3,  C1C4,
  C2C3,  
  C3C4.
*/

TEST(algorithms, find_triangular_faces)
{
    graph_lib::graph<std::string> g{ std::vector
                                                { std::pair{std::string{"A1"}, std::vector<std::string>{"A2","A5","B1","C1","C4"} },
                                                  std::pair{std::string{"A2"}, std::vector<std::string>{"A1","A3","B1","B2","C3","C4"} },
                                                  std::pair{std::string{"A3"}, std::vector<std::string>{"A2","A4","B2","B3","C2","C3"} },
                                                  std::pair{std::string{"A4"}, std::vector<std::string>{"A3","A5","B3","B4","C1","C2"} },
                                                  std::pair{std::string{"A5"}, std::vector<std::string>{"A1","A4","B1","B4","C1"} },
                                                  std::pair{std::string{"B1"}, std::vector<std::string>{"A1","A2","A5","B2","B4","B5"} },
                                                  std::pair{std::string{"B2"}, std::vector<std::string>{"A2","A3","B1","B3","B5"} },
                                                  std::pair{std::string{"B3"}, std::vector<std::string>{"A3","A4","B2","B4","B5"} },
                                                  std::pair{std::string{"B4"}, std::vector<std::string>{"A4","A5","B1","B3","B5"} },
                                                  std::pair{std::string{"B5"}, std::vector<std::string>{"B1","B2","B3","B4"} },
                                                  std::pair{std::string{"C1"}, std::vector<std::string>{"A1","A4","A5","C2","C3","C4"} },
                                                  std::pair{std::string{"C2"}, std::vector<std::string>{"A3","A4","C1","C3"} },
                                                  std::pair{std::string{"C3"}, std::vector<std::string>{"A2","A3","C1","C2","C4"} },
                                                  std::pair{std::string{"C4"}, std::vector<std::string>{"A1","A2","C1","C3"} } 
                                                }
                                   };

    

    auto results = graph_lib::find_triangular_faces(g);

    std::vector<std::tuple<std::string, std::string, std::string> > vec{ std::tuple{ "A1","A2","B1"}, std::tuple{ "A1","A2","C4"}, std::tuple{ "A1","B1","A2"},
                                                                         std::tuple{ "A1","B1","A5"}, std::tuple{ "A1","C4","A2"}, std::tuple{ "A1","C4","C1"},
                                                                         std::tuple{ "A2","A3","B2"}, std::tuple{ "A2","A3","C3"}, std::tuple{ "A2","B2","A3"},
                                                                         std::tuple{ "A2","B2","B1"}, std::tuple{ "A2","C4","C3"}, std::tuple{ "A3","A4","B3"},
                                                                         std::tuple{ "A3","A4","C2"}, std::tuple{ "A3","B3","A4"}, std::tuple{ "A3","B3","B2"},
                                                                         std::tuple{ "A3","C3","A2"}, std::tuple{ "A3","C3","C2"}, std::tuple{ "A4","A5","B4"},
                                                                         std::tuple{ "A4","A5","C1"}, std::tuple{ "A4","B4","A5"}, std::tuple{ "A4","B4","B3"},
                                                                         std::tuple{ "A4","C2","A3"}, std::tuple{ "A4","C2","C1"}, std::tuple{ "A5","A1","C1"},
                                                                         std::tuple{ "A5","B4","B1"}, std::tuple{ "B1","B2","B5"}, std::tuple{ "B1","B5","B2"},
                                                                         std::tuple{ "B1","B5","B4"}, std::tuple{ "B2","B5","B3"}, std::tuple{ "B3","B4","B5"},
                                                                         std::tuple{ "B4","B1","A5"}, std::tuple{ "B5","B3","B2"}, std::tuple{ "C1","C3","C2"},
                                                                         std::tuple{ "C1","C3","C4"},
                                                                        };
    ASSERT_EQ(results, vec);
}

/*
  A1, A2, A3, A4, A5, B1, B2, B3, B4, B5, C1,  C2,  C3,  C4
  and  edgese  in  corresponding:  
  A1A2,  A1A5,  A1B1,  A1C1, A1C4,  
  A2A3,  A2B1,  A2B2,  A2C3, A2C4,
  A3A4,  A3B2,  A3B3,  A3C2, A3C3,
  A4A5,  A4B3,  A4B4,  A4C1, A4C2,  
  A5B1,  A5B4,  A5C1,
  B1B2,  B1B4,  B1B5,  
  B2B3,  B2B5,  
  B3B4,  B3B5,  
  B4B5, 
  C1C2,  C1C3,  C1C4,
  C2C3,  
  C3C4.
*/
TEST(algorithms, cone_triangulation)
{
    graph_lib::graph<std::string> g{ std::vector
                                                { std::pair{std::string{"A1"}, std::vector<std::string>{"A2","A5","B1","C1","C4"} },
                                                  std::pair{std::string{"A2"}, std::vector<std::string>{"A1","A3","B1","B2","C3","C4"} },
                                                  std::pair{std::string{"A3"}, std::vector<std::string>{"A2","A4","B2","B3","C2","C3"} },
                                                  std::pair{std::string{"A4"}, std::vector<std::string>{"A3","A5","B3","B4","C1","C2"} },
                                                  std::pair{std::string{"A5"}, std::vector<std::string>{"A1","A4","B1","B4","C1"} },
                                                  std::pair{std::string{"B1"}, std::vector<std::string>{"A1","A2","A5","B2","B4","B5"} },
                                                  std::pair{std::string{"B2"}, std::vector<std::string>{"A2","A3","B1","B3","B5"} },
                                                  std::pair{std::string{"B3"}, std::vector<std::string>{"A3","A4","B2","B4","B5"} },
                                                  std::pair{std::string{"B4"}, std::vector<std::string>{"A4","A5","B1","B3","B5"} },
                                                  std::pair{std::string{"B5"}, std::vector<std::string>{"B1","B2","B3","B4"} },
                                                  std::pair{std::string{"C1"}, std::vector<std::string>{"A1","A4","A5","C2","C3","C4"} },
                                                  std::pair{std::string{"C2"}, std::vector<std::string>{"A3","A4","C1","C3"} },
                                                  std::pair{std::string{"C3"}, std::vector<std::string>{"A2","A3","C1","C2","C4"} },
                                                  std::pair{std::string{"C4"}, std::vector<std::string>{"A1","A2","C1","C3"} } 
                                                }
                                   };

    

    auto results = graph_lib::find_triangular_faces(g);

    std::vector<std::tuple<std::string, std::string, std::string> > vec{ std::tuple{ "A1","A2","B1"}, std::tuple{ "A1","A2","C4"}, std::tuple{ "A1","B1","A2"},
                                                                         std::tuple{ "A1","B1","A5"}, std::tuple{ "A1","C4","A2"}, std::tuple{ "A1","C4","C1"},
                                                                         std::tuple{ "A2","A3","B2"}, std::tuple{ "A2","A3","C3"}, std::tuple{ "A2","B2","A3"},
                                                                         std::tuple{ "A2","B2","B1"}, std::tuple{ "A2","C4","C3"}, std::tuple{ "A3","A4","B3"},
                                                                         std::tuple{ "A3","A4","C2"}, std::tuple{ "A3","B3","A4"}, std::tuple{ "A3","B3","B2"},
                                                                         std::tuple{ "A3","C3","A2"}, std::tuple{ "A3","C3","C2"}, std::tuple{ "A4","A5","B4"},
                                                                         std::tuple{ "A4","A5","C1"}, std::tuple{ "A4","B4","A5"}, std::tuple{ "A4","B4","B3"},
                                                                         std::tuple{ "A4","C2","A3"}, std::tuple{ "A4","C2","C1"}, std::tuple{ "A5","A1","C1"},
                                                                         std::tuple{ "A5","B4","B1"}, std::tuple{ "B1","B2","B5"}, std::tuple{ "B1","B5","B2"},
                                                                         std::tuple{ "B1","B5","B4"}, std::tuple{ "B2","B5","B3"}, std::tuple{ "B3","B4","B5"},
                                                                         std::tuple{ "B4","B1","A5"}, std::tuple{ "B5","B3","B2"}, std::tuple{ "C1","C3","C2"},
                                                                         std::tuple{ "C1","C3","C4"},
                                                                        };
    ASSERT_EQ(results, vec);

    auto cone_triang = graph_lib::cone_triangulation(results, std::string{"A2"});

    std::vector<std::tuple<std::string, std::string, std::string, std::string> > expected_cone{ std::tuple{ "A2","A1","B1","A5"}, std::tuple{ "A2","A1","C4","C1"}, std::tuple{ "A2","A3","A4","B3"}, 
                                                                                                std::tuple{ "A2","A3","A4","C2"}, std::tuple{ "A2","A3","B3","A4"}, std::tuple{ "A2","A3","B3","B2"}, 
                                                                                                std::tuple{ "A2","A3","C3","C2"}, std::tuple{ "A2","A4","A5","B4"}, std::tuple{ "A2","A4","A5","C1"}, 
                                                                                                std::tuple{ "A2","A4","B4","A5"}, std::tuple{ "A2","A4","B4","B3"}, std::tuple{ "A2","A4","C2","A3"}, 
                                                                                                std::tuple{ "A2","A4","C2","C1"}, std::tuple{ "A2","A5","A1","C1"}, std::tuple{ "A2","A5","B4","B1"}, 
                                                                                                std::tuple{ "A2","B1","B2","B5"}, std::tuple{ "A2","B1","B5","B2"}, std::tuple{ "A2","B1","B5","B4"}, 
                                                                                                std::tuple{ "A2","B2","B5","B3"}, std::tuple{ "A2","B3","B4","B5"}, std::tuple{ "A2","B4","B1","A5"}, 
                                                                                                std::tuple{ "A2","B5","B3","B2"}, std::tuple{ "A2","C1","C3","C2"}, std::tuple{ "A2","C1","C3","C4"}, 
                                                                                              };

  ASSERT_EQ(expected_cone, cone_triang);
}
