// Copyright [year] <Copyright Owner>
#ifndef MODULES_ALGORITHMS_INCLUDE_MAX_WEIGHT_MATCHING_H_
#define MODULES_ALGORITHMS_INCLUDE_MAX_WEIGHT_MATCHING_H_
#include "../../pch/include/precomp.h"

template <typename WeightType>
Matching max_weight_matching(const SM<WeightType>& graph) {
    int sizes = graph.edge_e.size();
    ++sizes;
    if (sizes == 1) {
        Matching R;
        return R;
    }
    std::vector <WeightType> W(sizes);
    W[0] = 0;
    W[1] = graph.weights[0];
    std::vector <Matching> M(sizes);
    M[1].edge_b.push_back(graph.edge_b[0]);
    M[1].edge_e.push_back(graph.edge_e[0]);
    for (int i = 2; i <= sizes - 1; i++) {
        if (graph.weights[i - 1] + W[i - 2] > W[i - 1]) {
            W[i] = graph.weights[i - 1] + W[i - 2];
            Matching temp;
            for (int j = 0; j < M[i - 2].edge_b.size(); j++) {
                temp.edge_b.push_back(M[i - 2].edge_b[j]);
                temp.edge_e.push_back(M[i - 2].edge_e[j]);
            }
            temp.edge_b.push_back(graph.edge_b[i - 1]);
            temp.edge_e.push_back(graph.edge_e[i - 1]);
            M[i] = temp;
        } else {
            W[i] = W[i - 1];
            Matching temp;
            for (int j = 0; j < M[i - 1].edge_b.size(); j++) {
                temp.edge_b.push_back(M[i - 1].edge_b[j]);
                temp.edge_e.push_back(M[i - 1].edge_e[j]);
            }
            M[i] = temp;
        }
    }
    M[sizes - 1].n = M[sizes - 1].edge_b.size();
    return M[sizes - 1];
}

#endif  // MODULES_ALGORITHMS_INCLUDE_MAX_WEIGHT_MATCHING_H_
