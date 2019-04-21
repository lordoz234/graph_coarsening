// Copyright [year] <Copyright Owner>
#include "../../modules/pch/include/precomp.h"
#include "gtest/gtest.h"

TEST(graph_coarsering, test1) {
    CSR<int> graph1 = washington_test<int>(2);
    for (int i = 0; i < graph1.n; i++) {
        std::cout << i << ": ";
        for (int j = graph1.offset[i]; j < graph1.offset[i + 1]; j++) {
            int to = graph1.edges[j];
            int weight = graph1.weights[j];
            std::cout << to << "-" << weight << " ";
        }
        std::cout << std::endl;
    }
    Matching gr = hard_matching(graph1);
    for (int i = 0; i < gr.n; i++) {
        std::cout << gr.edge_e[i] << " " << gr.edge_b[i] << std::endl;
    }
    CSR<int> graph = graph_coarsening1(graph1, gr);
    std::cout << std::endl;
    for (int i = 0; i < graph.n; i++) {
        std::cout << i << ": ";
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            int to = graph.edges[j];
            int weight = graph.weights[j];
            std::cout << to << "-" << weight << " ";
        }
        std::cout << std::endl;
    }
}

TEST(graph_coarsering, test2) {
    CSR<int> graph1 = washington_test<int>(2);
    int size = 0;
    for (int i = 0; i < graph1.n; i++) {
        for (int j = graph1.offset[i]; j < graph1.offset[i + 1]; j++) {
            ++size;
        }
    }
    Matching gr = hard_matching(graph1);
    CSR<int> graph = graph_coarsening1(graph1, gr);
    int size1 = 0;
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            ++size1;
        }
    }
    EXPECT_EQ(true, size > size1);
}

TEST(graph_coarsering, test3) {
    CSR<int> graph1 = washington_test<int>(3);
    int size = 0;
    for (int i = 0; i < graph1.n; i++) {
        for (int j = graph1.offset[i]; j < graph1.offset[i + 1]; j++) {
            ++size;
        }
    }
    Matching gr = hard_matching(graph1);
    CSR<int> graph = graph_coarsening1(graph1, gr);
    int size1 = 0;
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            ++size1;
        }
    }
    EXPECT_EQ(true, size > size1);
}

TEST(graph_coarsering, test4) {
    CSR<int> graph1 = washington_test<int>(4);
    int size = 0;
    for (int i = 0; i < graph1.n; i++) {
        for (int j = graph1.offset[i]; j < graph1.offset[i + 1]; j++) {
            ++size;
        }
    }
    Matching gr = hard_matching(graph1);
    CSR<int> graph = graph_coarsening1(graph1, gr);
    int size1 = 0;
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            ++size1;
        }
    }
    EXPECT_EQ(true, size > size1);
}

TEST(graph_coarsering, test5) {
    CSR<int> graph1 = zadeh_test<int>(2);
    int size = 0;
    for (int i = 0; i < graph1.n; i++) {
        for (int j = graph1.offset[i]; j < graph1.offset[i + 1]; j++) {
            ++size;
        }
    }
    Matching gr = hard_matching(graph1);
    CSR<int> graph = graph_coarsening1(graph1, gr);
    int size1 = 0;
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            ++size1;
        }
    }
    EXPECT_EQ(true, size > size1);
}

TEST(graph_coarsering, test6) {
    CSR<int> graph1 = zadeh_test<int>(3);
    int size = 0;
    for (int i = 0; i < graph1.n; i++) {
        for (int j = graph1.offset[i]; j < graph1.offset[i + 1]; j++) {
            ++size;
        }
    }
    Matching gr = hard_matching(graph1);
    CSR<int> graph = graph_coarsening1(graph1, gr);
    int size1 = 0;
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            ++size1;
        }
    }
    EXPECT_EQ(true, size > size1);
}

TEST(graph_coarsering, test7) {
    CSR<int> graph1 = zadeh_test<int>(4);
    int size = 0;
    for (int i = 0; i < graph1.n; i++) {
        for (int j = graph1.offset[i]; j < graph1.offset[i + 1]; j++) {
            ++size;
        }
    }
    Matching gr = hard_matching(graph1);
    CSR<int> graph = graph_coarsening1(graph1, gr);
    int size1 = 0;
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            ++size1;
        }
    }
    EXPECT_EQ(true, size > size1);
}

TEST(graph_coarsering, test8) {
    CSR<int> graph1 = cube_test<int>(2);
    int size = 0;
    for (int i = 0; i < graph1.n; i++) {
        for (int j = graph1.offset[i]; j < graph1.offset[i + 1]; j++) {
            ++size;
        }
    }
    Matching gr = hard_matching(graph1);
    CSR<int> graph = graph_coarsening1(graph1, gr);
    int size1 = 0;
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            ++size1;
        }
    }
    EXPECT_EQ(true, size > size1);
}

TEST(graph_coarsering, test9) {
    CSR<int> graph1 = cube_test<int>(3);
    int size = 0;
    for (int i = 0; i < graph1.n; i++) {
        for (int j = graph1.offset[i]; j < graph1.offset[i + 1]; j++) {
            ++size;
        }
    }
    Matching gr = hard_matching(graph1);
    CSR<int> graph = graph_coarsening1(graph1, gr);
    int size1 = 0;
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            ++size1;
        }
    }
    EXPECT_EQ(true, size > size1);
}

TEST(graph_coarsering, test10) {
    CSR<int> graph1 = cube_test<int>(4);
    int size = 0;
    for (int i = 0; i < graph1.n; i++) {
        for (int j = graph1.offset[i]; j < graph1.offset[i + 1]; j++) {
            ++size;
        }
    }
    Matching gr = hard_matching(graph1);
    CSR<int> graph = graph_coarsening1(graph1, gr);
    int size1 = 0;
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            ++size1;
        }
    }
    EXPECT_EQ(true, size > size1);
}

TEST(graph_coarsering, test11) {
    CSR<int> graph1 = chain_generator<int>(1, 2);
    int size = 0;
    for (int i = 0; i < graph1.n; i++) {
        for (int j = graph1.offset[i]; j < graph1.offset[i + 1]; j++) {
            ++size;
        }
    }
    Matching gr = hard_matching(graph1);
    CSR<int> graph = graph_coarsening1(graph1, gr);
    int size1 = 0;
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            ++size1;
        }
    }
    EXPECT_EQ(true, size > size1);
}

TEST(graph_coarsering, test12) {
    CSR<int> graph1 = chain_generator<int>(1, 3);
    int size = 0;
    for (int i = 0; i < graph1.n; i++) {
        for (int j = graph1.offset[i]; j < graph1.offset[i + 1]; j++) {
            ++size;
        }
    }
    Matching gr = hard_matching(graph1);
    CSR<int> graph = graph_coarsening1(graph1, gr);
    int size1 = 0;
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            ++size1;
        }
    }
    EXPECT_EQ(true, size > size1);
}

TEST(graph_coarsering, test13) {
    CSR<int> graph1 = chain_generator<int>(1, 4);
    int size = 0;
    for (int i = 0; i < graph1.n; i++) {
        for (int j = graph1.offset[i]; j < graph1.offset[i + 1]; j++) {
            ++size;
        }
    }
    Matching gr = hard_matching(graph1);
    CSR<int> graph = graph_coarsening1(graph1, gr);
    int size1 = 0;
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            ++size1;
        }
    }
    EXPECT_EQ(true, size > size1);
}

TEST(graph_coarsering, test14) {
    CSR<int> graph1 = cycle_generator<int>(2);
    int size = 0;
    for (int i = 0; i < graph1.n; i++) {
        for (int j = graph1.offset[i]; j < graph1.offset[i + 1]; j++) {
            ++size;
        }
    }
    Matching gr = hard_matching(graph1);
    CSR<int> graph = graph_coarsening1(graph1, gr);
    int size1 = 0;
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            ++size1;
        }
    }
    EXPECT_EQ(true, size > size1);
}

TEST(graph_coarsering, test15) {
    CSR<int> graph1 = cycle_generator<int>(3);
    int size = 0;
    for (int i = 0; i < graph1.n; i++) {
        for (int j = graph1.offset[i]; j < graph1.offset[i + 1]; j++) {
            ++size;
        }
    }
    Matching gr = hard_matching(graph1);
    CSR<int> graph = graph_coarsening1(graph1, gr);
    int size1 = 0;
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            ++size1;
        }
    }
    EXPECT_EQ(true, size > size1);
}

TEST(graph_coarsering, test16) {
    CSR<int> graph1 = cycle_generator<int>(4);
    int size = 0;
    for (int i = 0; i < graph1.n; i++) {
        for (int j = graph1.offset[i]; j < graph1.offset[i + 1]; j++) {
            ++size;
        }
    }
    Matching gr = hard_matching(graph1);
    CSR<int> graph = graph_coarsening1(graph1, gr);
    int size1 = 0;
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            ++size1;
        }
    }
    EXPECT_EQ(true, size > size1);
}

TEST(graph_coarsering, test17) {
    CSR<int> graph1 = stars_generator<int>(2);
    int size = 0;
    for (int i = 0; i < graph1.n; i++) {
        for (int j = graph1.offset[i]; j < graph1.offset[i + 1]; j++) {
            ++size;
        }
    }
    Matching gr = hard_matching(graph1);
    CSR<int> graph = graph_coarsening1(graph1, gr);
    int size1 = 0;
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            ++size1;
        }
    }
    EXPECT_EQ(true, size > size1);
}

TEST(graph_coarsering, test18) {
    CSR<int> graph1 = stars_generator<int>(3);
    int size = 0;
    for (int i = 0; i < graph1.n; i++) {
        for (int j = graph1.offset[i]; j < graph1.offset[i + 1]; j++) {
            ++size;
        }
    }
    Matching gr = hard_matching(graph1);
    CSR<int> graph = graph_coarsening1(graph1, gr);
    int size1 = 0;
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            ++size1;
        }
    }
    EXPECT_EQ(true, size > size1);
}

TEST(graph_coarsering, test19) {
    CSR<int> graph1 = stars_generator<int>(4);
    int size = 0;
    for (int i = 0; i < graph1.n; i++) {
        for (int j = graph1.offset[i]; j < graph1.offset[i + 1]; j++) {
            ++size;
        }
    }
    Matching gr = hard_matching(graph1);
    CSR<int> graph = graph_coarsening1(graph1, gr);
    int size1 = 0;
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            ++size1;
        }
    }
    EXPECT_EQ(true, size > size1);
}
