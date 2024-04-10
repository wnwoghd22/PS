#include <iostream>
#include <vector>
#include <queue>

const int MAX = 32'001;

int incoming[MAX];
std::vector<int> graph[MAX];
int N;

int lexical_topological_sort(std::vector<int>& container) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

    for (int i = 1; i <= N; ++i) {
        if (!incoming[i])
            pq.push(i);
    }

    while (!pq.empty()) {
        int v = pq.top(); pq.pop();
        container.push_back(v);

        for (const int& u : graph[v]) {
            if (!--incoming[u]) {
                pq.push(u);
            }
        }
    }

    return 0;
}

int main() {
    // std::ios_base::sync_with_stdio(0);
    // std::cin.tie(0); std::cout.tie(0);

    int M;

    std::cin >> N >> M;

    while (M--) {
        int a, b;

        std::cin >> a >> b;
        graph[a].push_back(b);
        incoming[b]++;
    }

    std::vector<int> data;
    lexical_topological_sort(data);

    for (const int& e : data)
        std::cout << e << ' ';

    return 0;
}