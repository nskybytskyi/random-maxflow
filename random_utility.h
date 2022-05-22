#ifndef RANDOM_UTILITY_HPP
#define RANDOM_UTILITY_HPP 1

#include "maxflow.h"

#include <random>

template <class RNG> 
mf_graph<int> random_graph(int n, int p, RNG& gen) {
    std::uniform_int_distribution<int> p_dist(1, 100), c_dist(1, 100);
    mf_graph<int> graph(n);
    for (int u = 0; u < n; ++u)
        for (int v = 0; v < n; ++v)
            if (u != v && p_dist(gen) <= p)
                graph.add_edge(u, v, c_dist(gen));
    return graph;
}

#include <algorithm>

template <class RNG> 
mf_graph<int> random_variant(mf_graph<int> graph, int r, RNG& gen) {
    std::uniform_int_distribution<int> c_dist(-r, r);
    const auto edges = graph.edges();
    const auto m = edges.size();
    for (int i = 0; i < m; ++i) {
        const auto new_cap = (edges[i].cap * (100 + c_dist(gen))) / 100;
        graph.change_edge(i, std::max(1, std::min(100, new_cap)), 0);
    }
    return graph;
}

mf_graph<int> stable_variant(mf_graph<int> graph, int r) {
    const auto edges = graph.edges();
    const auto m = edges.size();
    for (int i = 0; i < m; ++i) {
        const auto new_cap = (edges[i].cap * (100 - r)) / 100;
        graph.change_edge(i, std::max(1, new_cap), edges[i].flow);
    }
    return graph;
}

mf_graph<int> semi_stable_variant(int n, mf_graph<int> graph, int r) {
    const auto edges = graph.edges();
    const auto m = edges.size();
    for (int i = 0; i < m; ++i) {
        const auto edge = edges[i];
        if (edge.from == 1 || edge.to == n) {
            const auto new_cap = (edge.cap * (100 - r)) / 100;
            graph.change_edge(i, std::max(1, new_cap), edge.flow);
        } else {
            const auto new_cap = (edge.cap * (100 - (99 * r) / 100)) / 100;
            graph.change_edge(i, std::max(1, new_cap), edge.flow);
        }
    }
    return graph;
}

#endif // RANDOM_UTILITY_HPP
