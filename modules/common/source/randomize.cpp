// Copyright [year] <Copyright Owner>
#include <functional>
#include <vector>
#include <random>
#include <algorithm>
#include "../include/randomize.h"

static std::random_device rd;
static std::mt19937 generator(rd());
static int seed = -1;

static std::function <int
                        (int)> randomize_distribution[] = {
    [](int a) {
        if (seed != -1) {
            std::mt19937 fixed_generator(seed);
            return std::uniform_int_distribution<int>(0, a - 1)
                    (fixed_generator);
        } else {
            return std::uniform_int_distribution<int>(0, a - 1)
                    (generator);
        }
    },
    [](int a) {
        if (seed != -1) {
            std::mt19937 fixed_generator(seed);
            return std::normal_distribution<float>(0, a - 1)
                    (fixed_generator);
        } else {
            return std::normal_distribution<float>(0, a - 1)
                    (generator);
        }
    }
};

bool randomize_permutation(std::vector <int>* permutation, unsigned dist,
            int random_seed) {
    if (dist > sizeof(randomize_distribution))
        return false;
    seed = random_seed;
    std::random_shuffle(permutation->begin(), permutation->end(),
        randomize_distribution[dist]);
    seed = -1;
    return true;
}
