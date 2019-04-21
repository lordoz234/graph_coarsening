// Copyright [year] <Copyright Owner>
#ifndef MODULES_ALGORITHMS_INCLUDE_GRAPH_COARSERING1_H_
#define MODULES_ALGORITHMS_INCLUDE_GRAPH_COARSERING1_H_
#include "../../pch/include/precomp.h"

template <typename WeightType>
CSR<WeightType> graph_coarsening1(const CSR<WeightType>& graph,
                                 const Matching& match) {
    AL <int> new_graph;
    std::map <std::pair<int, int>, WeightType> m;
    std::set <std::pair<int, int>> is_match;
    for (int i = 0; i < match.n; i++) {
        is_match.insert(std::make_pair(match.edge_e[i], match.edge_b[i]));
        is_match.insert(std::make_pair(match.edge_b[i], match.edge_e[i]));
    }
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            int to = graph.edges[j];
            WeightType weight = graph.weights[j];
            if (is_match.find(std::make_pair(i, to)) != is_match.end()) {
                m[std::make_pair(i, to)] = weight;
            }
        }
    }
    std::vector <int> parent(graph.n);
    std::vector <int> rank(graph.n);
    auto make_set = [&] (int v) {
        parent[v] = v;
        rank[v] = 0;
    };
    std::function<int(int)> finds_set = [&] (int v) {
        if (v == parent[v])
            return v;
        return parent[v] = finds_set (parent[v]);
    };
    auto union_set = [&] (int a, int b) {
        a = finds_set(a);
        b = finds_set(b);
        if (a != b) {
            if (rank[a] < rank[b])
                std::swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b]) {
                ++rank[a];
            }
        }
    };
    std::map <int, WeightType> m1;
    for (int i = 0; i < graph.n; i++) {
        make_set(i);
    }
    for (int i = 0; i < match.n; i++) {
        union_set(match.edge_e[i], match.edge_b[i]);
        m1[finds_set(match.edge_e[i])] = m[std::make_pair(match.edge_e[i], match.edge_b[i])];
    }
    int new_size = graph.n;
    new_graph.edges.resize(new_size);
    new_graph.weights.resize(new_size);
    new_graph.n = new_size;
    for (int i = 0; i < graph.n; i++) {
        for (int j = graph.offset[i]; j < graph.offset[i + 1]; j++) {
            int to = graph.edges[j];
            WeightType weight = graph.weights[j];
            int a = finds_set(i);
            int b = finds_set(to);
            if (a == b) {
                continue;
            } else {
                new_graph.edges[a].push_back(b);
                new_graph.weights[a].push_back(weight);
            }
        }
    }
    return new_graph;
}

#endif  // MODULES_ALGORITHMS_INCLUDE_GRAPH_COARSERING1_H_
