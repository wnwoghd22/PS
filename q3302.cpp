#include <iostream>
#include <algorithm>

const int LEN = 1'000'000;

struct Task {
    int i, d;
    bool operator<(const Task& r) const { return d < r.d; }
} tasks[LEN];

int N, M, D;

bool process(int k) {
    int q = 0, d = 1;
    while (q < M) {
        for (int i = 0; i < k && q < M; ++i, ++q) {
            if (tasks[q].d + D < d) return false;
            if (tasks[q].d > d) break;
        }
        ++d;
    }
    return d <= N + 1;
}

int binary_search() {
    int l = 1, r = M, result = M, mid;
    while (l <= r) {
        mid = (l + r) / 2;
        if (process(mid)) {
            result = std::min(result, mid);
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return result;
}

int main() {
    std::cin.tie(0)->sync_with_stdio(0);

    std::cin >> N >> D >> M;
    for (int i = 0; i < M; ++i) {
        std::cin >> tasks[i].d;
        tasks[i].i = i + 1;
    }
    std::sort(tasks, tasks + M);
    int k = binary_search();
    std::cout << k << '\n';
    for (int i = 1, q = 0; i <= N; ++i) {
        for (int j = 0; j < k && q < M; ++j, ++q) {
            if (tasks[q].d > i) break;
            std::cout << tasks[q].i << ' ';
        }
        std::cout << "0\n";
    }
}