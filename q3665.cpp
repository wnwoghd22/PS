#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

int order[501];
int visited[501];
int incoming[501];
std::vector<int> graph[501];
bool switched[501][501];
int N;

int topological_sort(std::vector<int>& container) {
    std::queue<int> q;
    memset(visited, 0, sizeof visited);

    for (int i = 1; i <= N; ++i) {
        if (!incoming[i]) {
            q.push(i);
            visited[i] = true;
        }
    }

    while (!q.empty()) {
        if (q.size() > 1) return -1; // ambiguous

        int v = q.front(); q.pop();
        container.push_back(v);

        for (const int& u : graph[v]) {
            if (!--incoming[u]) {
                if (visited[u]) return 1; // cycle -> impossible
                visited[u] = true;
                q.push(u);
            }
        }
    }
    for (int i = 1; i <= N; ++i) {
        if (!visited[i]) // not visited -> cycle, impossible
            return 1;
    }

    return 0;
}

int main() {
    // std::ios_base::sync_with_stdio(0);
    // std::cin.tie(0); std::cout.tie(0);

    int T, M;

    std::cin >> T;
    while (T--) {
        memset(order, 0, sizeof order);
        memset(switched, 0, sizeof switched);
        memset(incoming, 0, sizeof incoming);
        for (std::vector<int>& v : graph) v.clear();

        std::cin >> N;
        for (int i = 1; i <= N; ++i) {
            std::cin >> order[i];
        }
        std::cin >> M;

        while (M--) {
            int a, b;
            std::cin >> a >> b;
            switched[a][b] = switched[b][a] = true;
        }

        for (int i = 1; i <= N; ++i) {
            for (int j = i + 1; j <= N; ++j) {
                int a = order[i], b = order[j];
                if (switched[a][b]) graph[b].push_back(a), incoming[a]++;
                else graph[a].push_back(b), incoming[b]++;
            }
        }

        std::vector<int> data;
        int result = topological_sort(data);

        if (result == 1) {
            std::cout << "IMPOSSIBLE\n";
        }
        else if (result == -1) {
            std::cout << "?\n";
        }
        else {
            for (const int& i : data)
                std::cout << i << ' ';
            std::cout << '\n';
        }
    }

    return 0;
}