#include "random_utility.h"
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(3);

    int t; cin >> t; while (t--) {
        int r;
        cin >> r;

        const int m = r + 1 + r;
        const int offset = r;

        mt19937 gen(0);
        int trials = 0;
        auto start = high_resolution_clock::now(), now = start;

        vector<vector<int>> cnt(m, vector<int>(m));

        do {
            auto s = random_disk_point(r, gen), t = random_disk_point(r, gen);
            auto p = random_disk_path(r, s, t, gen);
            for (auto v : p) {
                ++cnt[v.first + offset][v.second + offset];
            }
            ++trials;
            now = high_resolution_clock::now();
        } while (duration_cast<milliseconds>(now - start).count() < 1000);

        cout << trials << "\n";

        for (int x = -r; x <= r; ++x) {
            for (int y = -r; y <= r; ++y) {
                if (x * x + y * y <= r * r)
                    cout << cnt[x + offset][y + offset] * 1. / trials << " ";
                else
                    cout << 0. << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    return 0;
}
