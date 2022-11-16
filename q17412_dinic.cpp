#include <iostream>
#include <vector>
#include <queue>

const int MAX = 401;
const int INF = 1e9;

int N, P;
int c[MAX][MAX], f[MAX][MAX];
int work[MAX], level[MAX];
std::vector<int> A[MAX];

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

int main() {
    std::cin >> N >> P;

    int u, v;
    while (P--) {
        std::cin >> u >> v;
        A[u].push_back(v);
        A[v].push_back(u);
        c[u][v] = 1;
    }

    std::cout << dinic(1, 2);
}