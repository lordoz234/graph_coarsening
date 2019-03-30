// Copyright [year] <Copyright Owner>
#ifndef MODULES_DATA_STRUCTURES_INCLUDE_STRUCT_FOR_WEIGHT_MATCHING_H_
#define MODULES_DATA_STRUCTURES_INCLUDE_STRUCT_FOR_WEIGHT_MATCHING_H_
#include "../../pch/include/precomp.h"

template <typename WeightType>
struct SM {
 public:
    int n = 0;
    std::vector <int> edge_b;
    std::vector <int> edge_e;
    std::vector <WeightType> weights;
};

#endif  // MODULES_DATA_STRUCTURES_INCLUDE_STRUCT_FOR_WEIGHT_MATCHING_H_

