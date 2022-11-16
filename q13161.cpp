#include <iostream>
#include <vector>
#include <queue>

const int MAX = 503;
const int INF = 1e9;

int N, P;
int c[MAX][MAX], f[MAX][MAX];
int work[MAX], level[MAX], visited[MAX];
std::vector<int> A[MAX];
int source = 501, sink = 502;

bool bfs(int S, int T) {
    std::fill(level, level + MAX, -1);
    level[S] = 0;

    std::queue<int> q;
    q.push(S);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (const int& u : A[v]) {
            if (!~level[u] && c[v][u] - f[v][u] > 0) {
                level[u] = level[v] + 1;
                q.push(u);
            }
        }
    }
    return ~level[T];
}

int dfs(int here, int target, int flow) {
    if (here == target) return flow;

    for (int& i = work[here]; i < A[here].size(); i++) {
        int next = A[here][i];

        if (level[next] == level[here] + 1 && c[here][next] - f[here][next] > 0) {
            int ret = dfs(next, target, std::min(c[here][next] - f[here][next], flow));

            if (ret > 0) {
                f[here][next] += ret;
                f[next][here] -= ret;

                return ret;
            }
        }
    }

    return 0;
}

int dinic(int S, int T) {
    int totalFlow = 0;

    while (bfs(S, T)) {
        std::fill(work, work + MAX, 0);

        while (1) {
            int flow = dfs(S, T, INF);
            if (flow == 0)
                break;
            totalFlow += flow;
        }
    }

    return totalFlow;
}

void find_group(std::vector<int>& a, std::vector<int>& b) {
    std::queue<int> q;
    q.push(source);
    visited[source] = true;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (const int& u : A[v]) {
            if (!visited[u] && c[v][u] - f[v][u] > 0) {
                visited[u] = true;
                q.push(u);
            }
        }
    }
    for (int i = 1; i <= N; ++i) visited[i] ? a.push_back(i) : b.push_back(i);
}

int main() {
    std::cin >> N;

    for (int e, i = 1; i <= N; ++i) {
        std::cin >> e;
        if (e == 1) {
            A[source].push_back(i);
            A[i].push_back(source);
            c[source][i] = INF;
        }
        if (e == 2) {
            A[i].push_back(sink);
            A[sink].push_back(i);
            c[i][sink] = INF;
        }
    }

    for (int u = 1; u <= N; ++u) {
        for (int v = 1; v <= N; ++v) {
            std::cin >> c[u][v];
            if (u ^ v) A[u].push_back(v);
        }
    }

    std::cout << dinic(source, sink) << '\n';

    std::vector<int> a, b;
    find_group(a, b);
    for (const int& e : a) std::cout << e << ' '; std::cout << '\n';
    for (const int& e : b) std::cout << e << ' '; std::cout << '\n';
}