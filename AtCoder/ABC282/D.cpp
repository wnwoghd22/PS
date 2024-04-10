#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>

typedef long long int ll;
const int LEN = 200'000;
std::vector<int> graph[LEN];
int visited[LEN], p[LEN];
ll count1[LEN], count2[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;

    if (p[a] < p[b]) p[a] += p[b], p[b] = a;
    else p[b] += p[a], p[a] = b;

    return true;
}

bool bfs(int idx) {
    int u, color; bool result = true;
    std::queue<std::pair<int, int>> q;
    visited[idx] = 1;
    q.push({ idx, 1 });

    while (!q.empty()) {
        u = q.front().first, color = q.front().second, q.pop();
        for (const int& v : graph[u]) {
            if (!visited[v]) {
                join(u, v);
                visited[v] = color == 1 ? 2 : 1;
                q.push({ v, color == 1 ? 2 : 1 });
            }
            else if (visited[v] == color) result = false;
        }
    }
    return result;
}

int main() {
    ll V, E, u, v, result;
    ll count;

    result = true;
    memset(visited, 0, sizeof visited);
    memset(p, -1, sizeof p);

    std::cin >> V >> E;
    count = V * (V - 1) / 2 - E;

    while (E--) {
        std::cin >> u >> v;
        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }

    for (v = 0; v < V; ++v) {
        if (!visited[v] && !bfs(v)) {
            result = false;
            break;
        }
    }
    if (result) {
        for (v = 0; v < V; ++v) {
            if (visited[v] == 1) count1[find(v)]++;
            if (visited[v] == 2) count2[find(v)]++;
        }
        for (v = 0; v < V; ++v) {
            count -= count1[v] * (count1[v] - 1) / 2;
            count -= count2[v] * (count2[v] - 1) / 2;
        }
        std::cout << count;
    }
    else std::cout << 0;

    return 0;
}