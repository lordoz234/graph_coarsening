// Copyright [year] <Copyright Owner>
#ifndef MODULES_COMMON_INCLUDE_RANDOMIZE_H_
#define MODULES_COMMON_INCLUDE_RANDOMIZE_H_
#include "../../pch/include/precomp.h"

bool randomize_permutation(std::vector <int>* permutation, unsigned dist,
        int random_seed = -1);

#endif  // MODULES_COMMON_INCLUDE_RANDOMIZE_H_
