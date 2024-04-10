#include <iostream>
#include <vector>
#include <queue>

const int MAX = 303;
const int INF = 1e9;

int N, K, D;
int c[MAX][MAX], f[MAX][MAX];
int work[MAX], level[MAX];
std::vector<int> A[MAX];
int source = 301, sink = 302;

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

    for (int& i = work[here]; i < A[here].size(); ++i) {
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
    std::cin >> N >> K >> D;

    for (int i = 1; i <= D; ++i) {
        std::cin >> c[source][i];
        A[source].push_back(i);
        A[i].push_back(source);
    }

    for (int Z, e, i = 1; i <= N; ++i) {
        c[i + D][sink] = K;
        A[sink].push_back(i + D);
        A[i + D].push_back(sink);
        std::cin >> Z;
        while (Z--) {
            std::cin >> e;
            c[e][i + D] = 1;
            A[e].push_back(i + D);
            A[i + D].push_back(e);
        }
    }

    std::cout << dinic(source, sink);
}