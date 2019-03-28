// Copyright [year] <Copyright Owner>
#ifndef TESTS_INCLUDE_RANDOM_MATCHING_PARAMETRIC_TEST_H_
#define TESTS_INCLUDE_RANDOM_MATCHING_PARAMETRIC_TEST_H_
#include "../../modules/pch/include/precomp.h"
#include "gtest/gtest.h"

static std::random_device rd;
static std::mt19937 generator(rd());

class random_matching_washington_test : public testing::TestWithParam<int> {
 public:
    random_matching_washington_test() {
        value = GetParam();
    }

    void correct_random_matching_on_csr_max_size() {
        CSR<int> csr = washington_test<int>(value);
        std::vector <char> used(csr.n, 0);
        auto matching = random_matching(csr);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < csr.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        for (int i = 0; i < csr.n; ++i) {
            if (!used[i]) {
                for (int j = csr.offset[i]; j < csr.offset[i+1]; ++j) {
                    if (csr.edges[j] != i) {
                        ASSERT_NE(0, used[csr.edges[j]]);
                    }
                }
            }
        }
    }

    void correct_random_matching_on_al_max_size() {
        AL<int> al = washington_test<int>(value);
        std::vector <char> used(al.n, 0);
        auto matching = random_matching(al);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < al.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        for (int i = 0; i < al.n; ++i) {
            if (!used[i]) {
                for (unsigned j = 0; j < al.edges[i].size(); ++j) {
                    if (al.edges[i][j] != i) {
                        ASSERT_NE(0, used[al.edges[i][j]]);
                    }
                }
            }
        }
    }

    void correct_random_matching_on_csr_variable_size() {
        CSR<int> csr = washington_test<int>(value);
        std::vector <char> used(csr.n, 0);
        int matching_size =
            std::uniform_int_distribution<int>(0, csr.n / 2)(generator);
        auto matching = random_matching(csr, 0, matching_size);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < csr.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        ASSERT_TRUE(matching_size >= static_cast<int>(matching.edge_b.size()));
    }

    void correct_random_matching_on_al_variable_size() {
        AL<int> al = washington_test<int>(value);
        std::vector <char> used(al.n, 0);
        int matching_size =
            std::uniform_int_distribution<int>(0, al.n / 2)(generator);
        auto matching = random_matching(al, 0, matching_size);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < al.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        ASSERT_TRUE(matching_size >= static_cast<int>(matching.edge_b.size()));
    }

 private:
    int value;
};

class random_matching_zadeh_test : public testing::TestWithParam<int> {
 public:
    random_matching_zadeh_test() {
        value = GetParam();
    }

    void correct_random_matching_on_csr_max_size() {
        CSR<int> csr = zadeh_test<int>(value);
        std::vector <char> used(csr.n, 0);
        auto matching = random_matching(csr);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < csr.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        for (int i = 0; i < csr.n; ++i) {
            if (!used[i]) {
                for (int j = csr.offset[i]; j < csr.offset[i+1]; ++j) {
                    if (csr.edges[j] != i) {
                        ASSERT_NE(0, used[csr.edges[j]]);
                    }
                }
            }
        }
    }

    void correct_random_matching_on_al_max_size() {
        AL<int> al = zadeh_test<int>(value);
        std::vector <char> used(al.n, 0);
        auto matching = random_matching(al);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < al.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        for (int i = 0; i < al.n; ++i) {
            if (!used[i]) {
                for (unsigned j = 0; j < al.edges[i].size(); ++j) {
                    if (al.edges[i][j] != i) {
                        ASSERT_NE(0, used[al.edges[i][j]]);
                    }
                }
            }
        }
    }

    void correct_random_matching_on_csr_variable_size() {
        CSR<int> csr = zadeh_test<int>(value);
        std::vector <char> used(csr.n, 0);
        int matching_size =
            std::uniform_int_distribution<int>(0, csr.n / 2)(generator);
        auto matching = random_matching(csr, 0, matching_size);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < csr.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        ASSERT_TRUE(matching_size >= static_cast<int>(matching.edge_b.size()));
    }

    void correct_random_matching_on_al_variable_size() {
        AL<int> al = zadeh_test<int>(value);
        std::vector <char> used(al.n, 0);
        int matching_size =
            std::uniform_int_distribution<int>(0, al.n / 2)(generator);
        auto matching = random_matching(al, 0, matching_size);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < al.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        ASSERT_TRUE(matching_size >= static_cast<int>(matching.edge_b.size()));
    }

 private:
    int value;
};

class random_matching_cube_test : public testing::TestWithParam<int> {
 public:
    random_matching_cube_test() {
        value = GetParam();
    }

    void correct_random_matching_on_csr_max_size() {
        CSR<int> csr = cube_test<int>(value);
        std::vector <char> used(csr.n, 0);
        auto matching = random_matching(csr);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < csr.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        for (int i = 0; i < csr.n; ++i) {
            if (!used[i]) {
                for (int j = csr.offset[i]; j < csr.offset[i+1]; ++j) {
                    if (csr.edges[j] != i) {
                        ASSERT_NE(0, used[csr.edges[j]]);
                    }
                }
            }
        }
    }

    void correct_random_matching_on_al_max_size() {
        AL<int> al = cube_test<int>(value);
        std::vector <char> used(al.n, 0);
        auto matching = random_matching(al);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < al.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        for (int i = 0; i < al.n; ++i) {
            if (!used[i]) {
                for (unsigned j = 0; j < al.edges[i].size(); ++j) {
                    if (al.edges[i][j] != i) {
                        ASSERT_NE(0, used[al.edges[i][j]]);
                    }
                }
            }
        }
    }

    void correct_random_matching_on_csr_variable_size() {
        CSR<int> csr = cube_test<int>(value);
        std::vector <char> used(csr.n, 0);
        int matching_size =
            std::uniform_int_distribution<int>(0, csr.n / 2)(generator);
        auto matching = random_matching(csr, 0, matching_size);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < csr.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        ASSERT_TRUE(matching_size >= static_cast<int>(matching.edge_b.size()));
    }

    void correct_random_matching_on_al_variable_size() {
        AL<int> al = cube_test<int>(value);
        std::vector <char> used(al.n, 0);
        int matching_size =
            std::uniform_int_distribution<int>(0, al.n / 2)(generator);
        auto matching = random_matching(al, 0, matching_size);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < al.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        ASSERT_TRUE(matching_size >= static_cast<int>(matching.edge_b.size()));
    }

 private:
    int value;
};

class random_matching_cycle_generator : public testing::TestWithParam<int> {
 public:
    random_matching_cycle_generator() {
        value = GetParam();
    }

    void correct_random_matching_on_csr_max_size() {
        CSR<int> csr = cycle_generator<int>(value);
        std::vector <char> used(csr.n, 0);
        auto matching = random_matching(csr);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < csr.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        for (int i = 0; i < csr.n; ++i) {
            if (!used[i]) {
                for (int j = csr.offset[i]; j < csr.offset[i+1]; ++j) {
                    if (csr.edges[j] != i) {
                        ASSERT_NE(0, used[csr.edges[j]]);
                    }
                }
            }
        }
    }

    void correct_random_matching_on_al_max_size() {
        AL<int> al = cycle_generator<int>(value);
        std::vector <char> used(al.n, 0);
        auto matching = random_matching(al);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < al.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        for (int i = 0; i < al.n; ++i) {
            if (!used[i]) {
                for (unsigned j = 0; j < al.edges[i].size(); ++j) {
                    if (al.edges[i][j] != i) {
                        ASSERT_NE(0, used[al.edges[i][j]]);
                    }
                }
            }
        }
    }

    void correct_random_matching_on_csr_variable_size() {
        CSR<int> csr = cycle_generator<int>(value);
        std::vector <char> used(csr.n, 0);
        int matching_size =
            std::uniform_int_distribution<int>(0, csr.n / 2)(generator);
        auto matching = random_matching(csr, 0, matching_size);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < csr.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        ASSERT_TRUE(matching_size >= static_cast<int>(matching.edge_b.size()));
    }

    void correct_random_matching_on_al_variable_size() {
        AL<int> al = cycle_generator<int>(value);
        std::vector <char> used(al.n, 0);
        int matching_size =
            std::uniform_int_distribution<int>(0, al.n / 2)(generator);
        auto matching = random_matching(al, 0, matching_size);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < al.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        ASSERT_TRUE(matching_size >= static_cast<int>(matching.edge_b.size()));
    }

 private:
    int value;
};

class random_matching_stars_generator : public testing::TestWithParam<int> {
 public:
    random_matching_stars_generator() {
        value = GetParam();
    }

    void correct_random_matching_on_csr_max_size() {
        CSR<int> csr = stars_generator<int>(value);
        std::vector <char> used(csr.n, 0);
        auto matching = random_matching(csr);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < csr.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        for (int i = 0; i < csr.n; ++i) {
            if (!used[i]) {
                for (int j = csr.offset[i]; j < csr.offset[i+1]; ++j) {
                    if (csr.edges[j] != i) {
                        ASSERT_NE(0, used[csr.edges[j]]);
                    }
                }
            }
        }
    }

    void correct_random_matching_on_al_max_size() {
        AL<int> al = stars_generator<int>(value);
        std::vector <char> used(al.n, 0);
        auto matching = random_matching(al);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < al.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        for (int i = 0; i < al.n; ++i) {
            if (!used[i]) {
                for (unsigned j = 0; j < al.edges[i].size(); ++j) {
                    if (al.edges[i][j] != i) {
                        ASSERT_NE(0, used[al.edges[i][j]]);
                    }
                }
            }
        }
    }

    void correct_random_matching_on_csr_variable_size() {
        CSR<int> csr = stars_generator<int>(value);
        std::vector <char> used(csr.n, 0);
        int matching_size =
            std::uniform_int_distribution<int>(0, csr.n / 2)(generator);
        auto matching = random_matching(csr, 0, matching_size);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < csr.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        ASSERT_TRUE(matching_size >= static_cast<int>(matching.edge_b.size()));
    }

    void correct_random_matching_on_al_variable_size() {
        AL<int> al = stars_generator<int>(value);
        std::vector <char> used(al.n, 0);
        int matching_size =
            std::uniform_int_distribution<int>(0, al.n / 2)(generator);
        auto matching = random_matching(al, 0, matching_size);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < al.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        ASSERT_TRUE(matching_size >= static_cast<int>(matching.edge_b.size()));
    }

 private:
    int value;
};

class random_matching_chain_generator :
                    public testing::TestWithParam<std::pair <int, int>> {
 public:
    random_matching_chain_generator() {
        value = GetParam();
    }

    void correct_random_matching_on_csr_max_size() {
        CSR<int> csr = chain_generator<int>(value.first, value.second);
        std::vector <char> used(csr.n, 0);
        auto matching = random_matching(csr);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < csr.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        for (int i = 0; i < csr.n; ++i) {
            if (!used[i]) {
                for (int j = csr.offset[i]; j < csr.offset[i+1]; ++j) {
                    if (csr.edges[j] != i) {
                        ASSERT_NE(0, used[csr.edges[j]]);
                    }
                }
            }
        }
    }

    void correct_random_matching_on_al_max_size() {
        AL<int> al = chain_generator<int>(value.first, value.second);
        std::vector <char> used(al.n, 0);
        auto matching = random_matching(al);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < al.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        for (int i = 0; i < al.n; ++i) {
            if (!used[i]) {
                for (unsigned j = 0; j < al.edges[i].size(); ++j) {
                    if (al.edges[i][j] != i) {
                        ASSERT_NE(0, used[al.edges[i][j]]);
                    }
                }
            }
        }
    }

    void correct_random_matching_on_csr_variable_size() {
        CSR<int> csr = chain_generator<int>(value.first, value.second);
        std::vector <char> used(csr.n, 0);
        int matching_size =
            std::uniform_int_distribution<int>(0, csr.n / 2)(generator);
        auto matching = random_matching(csr, 0, matching_size);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < csr.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        ASSERT_TRUE(matching_size >= static_cast<int>(matching.edge_b.size()));
    }

    void correct_random_matching_on_al_variable_size() {
        AL<int> al = chain_generator<int>(value.first, value.second);
        std::vector <char> used(al.n, 0);
        int matching_size =
            std::uniform_int_distribution<int>(0, al.n / 2)(generator);
        auto matching = random_matching(al, 0, matching_size);
        for (int i = 0; i < matching.n; ++i) {
            ++used[matching.edge_b[i]];
            ++used[matching.edge_e[i]];
        }
        for (int i = 0; i < al.n; ++i)
            ASSERT_TRUE((used[i] == 0) || (used[i] == 1));
        ASSERT_TRUE(matching_size >= static_cast<int>(matching.edge_b.size()));
    }

 private:
    std::pair <int, int> value;
};

std::vector <int> generate_samples(int from, int to, int n = 20) {
    std::vector <int> result;
    for (int i = 0; i < n; ++i)
        result.push_back(std::uniform_int_distribution<int>(from, to)
                                (generator));
    return result;
}

std::vector <std::pair <int, int>>
            generate_pair_samples(int from, int to, int n = 20) {
    std::vector <int> r1 = generate_samples(from, to, 3);
    std::vector <int> r2 = generate_samples(from, to, 3);
    std::vector <std::pair <int, int>> result;
    for (int i = 0; i < n; ++i)
        result.emplace_back(r1[i], r2[i]);
    return result;
}

std::vector <int> washington_samples = generate_samples(0, 100, 3);  // was 1e5
std::vector <int> zadeh_samples = generate_samples(0, 50, 3);  // was 1000
std::vector <int> cube_samples = generate_samples(0, 10, 3);  // was 100
std::vector <int> cycle_samples = generate_samples(0, 1000, 3);
std::vector <int> stars_samples = generate_samples(0, 200, 3);
std::vector <std::pair <int, int>> chain_samples =
                                            generate_pair_samples(0, 50, 3);

TEST_P(random_matching_washington_test, max_size_on_csr) {
    correct_random_matching_on_csr_max_size();
}

TEST_P(random_matching_washington_test, max_size_on_al) {
    correct_random_matching_on_al_max_size();
}

TEST_P(random_matching_washington_test, variable_size_on_csr) {
    correct_random_matching_on_csr_variable_size();
}

TEST_P(random_matching_washington_test, variable_size_on_al) {
    correct_random_matching_on_al_variable_size();
}

TEST_P(random_matching_zadeh_test, max_size_on_csr) {
    correct_random_matching_on_csr_max_size();
}

TEST_P(random_matching_zadeh_test, max_size_on_al) {
    correct_random_matching_on_al_max_size();
}

TEST_P(random_matching_zadeh_test, variable_size_on_csr) {
    correct_random_matching_on_csr_variable_size();
}

TEST_P(random_matching_zadeh_test, variable_size_on_al) {
    correct_random_matching_on_al_variable_size();
}

TEST_P(random_matching_cube_test, max_size_on_csr) {
    correct_random_matching_on_csr_max_size();
}

TEST_P(random_matching_cube_test, max_size_on_al) {
    correct_random_matching_on_al_max_size();
}

TEST_P(random_matching_cube_test, variable_size_on_csr) {
    correct_random_matching_on_csr_variable_size();
}

TEST_P(random_matching_cube_test, variable_size_on_al) {
    correct_random_matching_on_al_variable_size();
}

TEST_P(random_matching_cycle_generator, max_size_on_csr) {
    correct_random_matching_on_csr_max_size();
}

TEST_P(random_matching_cycle_generator, max_size_on_al) {
    correct_random_matching_on_al_max_size();
}

TEST_P(random_matching_cycle_generator, variable_size_on_csr) {
    correct_random_matching_on_csr_variable_size();
}

TEST_P(random_matching_cycle_generator, variable_size_on_al) {
    correct_random_matching_on_al_variable_size();
}

TEST_P(random_matching_stars_generator, max_size_on_csr) {
    correct_random_matching_on_csr_max_size();
}

TEST_P(random_matching_stars_generator, max_size_on_al) {
    correct_random_matching_on_al_max_size();
}

TEST_P(random_matching_stars_generator, variable_size_on_csr) {
    correct_random_matching_on_csr_variable_size();
}

TEST_P(random_matching_stars_generator, variable_size_on_al) {
    correct_random_matching_on_al_variable_size();
}

TEST_P(random_matching_chain_generator, max_size_on_csr) {
    correct_random_matching_on_csr_max_size();
}

TEST_P(random_matching_chain_generator, max_size_on_al) {
    correct_random_matching_on_al_max_size();
}

TEST_P(random_matching_chain_generator, variable_size_on_csr) {
    correct_random_matching_on_csr_variable_size();
}

TEST_P(random_matching_chain_generator, variable_size_on_al) {
    correct_random_matching_on_al_variable_size();
}

INSTANTIATE_TEST_SUITE_P(random_matching_test1, random_matching_washington_test,
                    testing::ValuesIn(washington_samples));

INSTANTIATE_TEST_SUITE_P(random_matching_test2, random_matching_zadeh_test,
                    testing::ValuesIn(zadeh_samples));

INSTANTIATE_TEST_SUITE_P(random_matching_test3, random_matching_cube_test,
                    testing::ValuesIn(cube_samples));

INSTANTIATE_TEST_SUITE_P(random_matching_test4, random_matching_cycle_generator,
                    testing::ValuesIn(cycle_samples));

INSTANTIATE_TEST_SUITE_P(random_matching_test5, random_matching_stars_generator,
                    testing::ValuesIn(stars_samples));

INSTANTIATE_TEST_SUITE_P(random_matching_test6, random_matching_chain_generator,
                    testing::ValuesIn(chain_samples));

#endif  // TESTS_INCLUDE_RANDOM_MATCHING_PARAMETRIC_TEST_H_
