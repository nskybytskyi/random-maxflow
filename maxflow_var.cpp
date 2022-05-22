#include "maxflow.h"
#include "random_utility.h"
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(2);

    int t; cin >> t; while (t--) {
        int n, p, r;
        cin >> n >> p >> r;

        mt19937 gen(0);
        int trials = 0, stable_flow = 0, semi_stable_flow = 0;
        auto start = high_resolution_clock::now(), now = start;

        do {
            auto graph = random_graph(n, p, gen);
            auto stable = stable_variant(graph, r);
            const auto stable_flow_inner = stable.flow(0, n - 1);
            auto semi_stable = semi_stable_variant(n, graph, r);
            const auto semi_stable_flow_inner = semi_stable.flow(0, n - 1);

            auto start_inner = high_resolution_clock::now(), now_inner = start_inner;
            do {
                auto variant = random_variant(graph, r, gen);
                vector<vector<int>> variant_cap(n, vector<int>(n));
                for (auto edge : variant.edges())
                    variant_cap[edge.from][edge.to] = edge.cap;

                bool stable_good = true;
                for (auto edge : stable.edges())
                    stable_good &= edge.flow <= variant_cap[edge.from][edge.to];
                if (stable_good)
                    stable_flow += stable_flow_inner;

                bool semi_stable_good = true;
                for (auto edge : semi_stable.edges())
                    semi_stable_good &= edge.flow <= variant_cap[edge.from][edge.to];
                if (semi_stable_good)
                    semi_stable_flow += semi_stable_flow_inner;

                ++trials;
                now_inner = high_resolution_clock::now();
            } while (duration_cast<milliseconds>(now_inner - start_inner).count() < 100);
            now = high_resolution_clock::now();
        } while (duration_cast<milliseconds>(now - start).count() < 10'000);

        cout << trials << " " << stable_flow * 1. / trials << " " << semi_stable_flow * 1. / trials << "\n";
    }

    return 0;
}
