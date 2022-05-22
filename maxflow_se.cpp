#include "maxflow.h"
#include "random_utility.h"
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(2);

    int t; cin >> t; while (t--) {
        int n, p;
        cin >> n >> p;

        mt19937 gen(0);
        int trials = 0, flow = 0;
        auto start = high_resolution_clock::now(), now = start;
        vector<vector<int>> cnt(n, vector<int>(n));

        do {
            auto graph = random_graph(n, p, gen);
            flow += graph.flow(0, n - 1);
            for (auto edge : graph.edges())
                if (edge.cap == edge.flow)
                    ++cnt[edge.from][edge.to];
            now = high_resolution_clock::now();
            ++trials;
        } while (duration_cast<milliseconds>(now - start).count() < 10'000);

        int st_edges = 0, uv_edges = 0;
        for (int u = 0; u < n; ++u)
            for (int v = 0; v < n; ++v) {
                if (u == 0 || v == n - 1)
                    st_edges += cnt[u][v];
                else
                    uv_edges ++ cnt[u][v]; 
            }
        cout << trials << " " << flow * 1. / trials << \
            " " << st_edges * 1. / trials << " " << uv_edges * 1. / trials <<  "\n";

        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v)
                cout << cnt[u][v] * 1. / trials << " ";
            cout << "\n";
        }
        cout << "\n";
    }

    return 0;
}
