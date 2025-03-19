#include <iostream>
#include <queue>

const int LEN = 3'001;

int A[LEN], B[LEN], C[LEN];
int M[LEN][LEN];
std::vector<int> graph[LEN];
int incoming[LEN];
int N;

void topological_sort() {
    std::queue<int> q;

    for (int i = 1; i <= N; ++i) {
        if (!incoming[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int v = q.front(); q.pop();

        std::cout << v << ' ';

        for (const int& u : graph[v]) {
            if (!--incoming[u]) {
                q.push(u);
            }
        }
    }
}

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; ++i) {
        std::cin >> A[i];
        for (int j = 1; j < i; ++j) {
            ++M[A[j]][A[i]];
        }
    }
    for (int i = 1; i <= N; ++i) {
        std::cin >> B[i];
        for (int j = 1; j < i; ++j) {
            ++M[B[j]][B[i]];
        }
    }
    for (int i = 1; i <= N; ++i) {
        std::cin >> C[i];
        for (int j = 1; j < i; ++j) {
            ++M[C[j]][C[i]];
        }
    }
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (M[i][j] >= 2) {
                graph[i].push_back(j);
                incoming[j]++;
            }
        }
    }
    topological_sort();
}