// Copyright [year] <Copyright Owner>
#include <iostream>
#include <vector>
#include <random>
#include "../../3rdparty/gtest/gtest.h"
#include "../../modules/data_structures/include/graph.h"
#include "../../modules/data_structures/include/csr.h"
#include "../../modules/generators/include/generator.h"
#include "../../modules/algorithms/include/random_matching.h"
#include "../../modules/algorithms/include/hard_matching.h"

static std::random_device rd;
static std::mt19937 generator(rd());

TEST(csr_test, basic_washington_test_generates) {
    ASSERT_NO_THROW(washington_test(20));
}

TEST(csr_test, random_washington_test_generates) {
    int n = std::uniform_int_distribution<int>(1, 1e5)(generator);
    ASSERT_NO_THROW(washington_test(n, true));
}

TEST(csr_test, basic_zadeh_test_generates_and_converts_to_csr) {
    ASSERT_NO_THROW(CSR csr = zadeh_test(20));
}

TEST(csr_test, random_zadeh_test_generates_and_converts_to_csr) {
    int n = std::uniform_int_distribution<int>(1, 1e3)(generator);
    ASSERT_NO_THROW(CSR csr = zadeh_test(n, true));
}

TEST(csr_test, graph_file_operations) {
    CSR graph = washington_test(20);
    ASSERT_NO_THROW(ASSERT_EQ(true, graph.write("csr.bin")));
    ASSERT_NO_THROW(ASSERT_EQ(true, graph.read("csr.bin")));
}

TEST(csr_test, run_bfs_on_basic_washington_test) {
    CSR csr = washington_test(2);
    ASSERT_EQ(6, csr.bfs(0, csr.n - 1));
}

TEST(csr_test, run_dfs_on_basic_washington_test) {
    CSR csr = washington_test(2);
    std::vector <int> dfs_result = csr.dfs(0);
    std::vector <int> expected_dfs_result = {1, 2, 3, 3, 4, 4, 5, 6, 7};
    ASSERT_EQ(expected_dfs_result, dfs_result);
}

TEST(csr_test, run_Dijkstra_on_not_weighted_basic_washington_test) {
    CSR csr = washington_test(2);
    ASSERT_EQ(csr.Dijkstra(0, csr.n - 1), csr.bfs(0, csr.n - 1));
}

TEST(al_test, run_Dijkstra_on_not_weighted_basic_washington_test) {
    AL al = washington_test(2);
    ASSERT_EQ(al.Dijkstra(0, al.n - 1), al.bfs(0, al.n - 1));
}

TEST(csr_test, correct_random_matching_on_basic_washington_test) {
    for (int counter = 0; counter < 1000; ++counter) {
        CSR csr = washington_test(2);
        std::vector <char> used(csr.n, 0);
        auto matching = random_matching(csr);
        for (int i = 0; i < matching.n; ++i)
            used[matching.edge_b[i]] = used[matching.edge_e[i]] = true;
        for (int i = 0; i < csr.n; ++i) {
            if (!used[i]) {
                for (int j = csr.offset[i]; j < csr.offset[i+1]; ++j)
                    ASSERT_EQ(true, used[csr.edges[j].first]);
            }
        }
    }
}

TEST(csr_test, run_dfs_on_random_washington_test) {
    int n = std::uniform_int_distribution<int>(1, 1e3)(generator);
    CSR csr = washington_test(n, true);
    std::vector <int> expected_dfs_result;
    expected_dfs_result.push_back(1);
    expected_dfs_result.push_back(2);
    for (int i = 0; i < n; ++i)
        expected_dfs_result.push_back(3);
    for (int i = 0; i < n; ++i)
        expected_dfs_result.push_back(4);
    for (int i = 0; i <= n; ++i)
        expected_dfs_result.push_back(i + 5);
    std::vector <int> dfs_result = csr.dfs(0);
    ASSERT_EQ(expected_dfs_result, dfs_result);
}


