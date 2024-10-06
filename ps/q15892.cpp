#include <iostream>
#include <vector>
#include <queue>

const int MAX = 301;
const int INF = 1e9;

int N, M;
int c[MAX][MAX], f[MAX][MAX];
int work[MAX], level[MAX];
std::vector<int> A[MAX];

bool bfs(int S, int T) {
    std::fill(level, level + MAX, -1);

    level[S] = 0;

    std::queue<int> q;

    q.push(S);

    while (!q.empty())
    {
        int here = q.front();
        q.pop();

        for (int i = 0; i < A[here].size(); i++)
        {
            int next = A[here][i];

            if (!~level[next] && c[here][next] - f[here][next] > 0)
            {
                level[next] = level[here] + 1;
                q.push(next);
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
    std::cin.tie(0)->sync_with_stdio(0);

    std::cin >> N >> M;

    int u, v, w;
    while (M--) {
        std::cin >> u >> v >> w;
        A[u].push_back(v);
        A[v].push_back(u);
        c[u][v] = c[v][u] += w;
    }

    std::cout << dinic(1, N);
}