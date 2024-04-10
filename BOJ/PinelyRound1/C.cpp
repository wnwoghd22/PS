#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <cstring>

const int MAX = 100;

int incoming[MAX];
std::vector<int> graph[MAX];
std::set<int> set[MAX];
int N, E, b;

int topological_sort() {
    std::queue<int> q;
    E = 1;

    for (int i = 0; i < N; ++i) {
        if (!incoming[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int v = q.front(); q.pop();
        set[v].insert(E++);

        for (const int& u : graph[v]) {
            for (const int& e : set[v]) {
                set[u].insert(e);
            }
            if (!--incoming[u]) {
                q.push(u);
            }
        }
    }

    return 0;
}

int main() {
    int T;

    std::cin >> T;
    while (T--) {
        memset(incoming, 0, sizeof incoming);
        for (std::vector<int>& v : graph) v.clear();
        for (std::set<int>& v : set) v.clear();

        std::cin >> N;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                scanf("%1d", &b);
                if (b) {
                    graph[i].push_back(j);
                    incoming[j]++;
                }
            }
        }
        int result = topological_sort();

        for (int i = 0; i < N; ++i) {
            std::cout << set[i].size() << ' ';
            for (const int& e : set[i])
                std::cout << e << ' ';
            std::cout << '\n';
        }
    }
}