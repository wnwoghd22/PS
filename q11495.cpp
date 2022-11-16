#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

const int MAX = 2503;
const int INF = 1e9;

int T, N, M, S;
int c[MAX][MAX], f[MAX][MAX];
int work[MAX], level[MAX];
std::vector<int> A[MAX];
int source = 2501, sink = 2502;
int dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, -1, 1 };

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
    std::cin >> T;
    while (T--) {
        S = 0;
        for (std::vector<int>& v : A) v.clear();
        memset(f, 0, sizeof f);
        memset(c, 0, sizeof c);

        std::cin >> N >> M;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                int idx = i * M + j + 1;
                if ((i ^ j) & 1) {
                    std::cin >> c[source][idx];
                    S += c[source][idx];

                    A[source].push_back(idx);
                    A[idx].push_back(source);

                    for (int d = 0; d < 4; ++d) {
                        int di = i + dx[d], dj = j + dy[d];
                        int dn = M * dx[d] + dy[d];

                        if (di < 0 || di >= N || dj < 0 || dj >= M) continue;

                        A[idx].push_back(idx + dn);
                        A[idx + dn].push_back(idx);
                        c[idx][idx + dn] = INF;
                    }
                }
                else {
                    std::cin >> c[idx][sink];
                    S += c[idx][sink];

                    A[sink].push_back(idx);
                    A[idx].push_back(sink);
                }
            }
        }

        std::cout << S - dinic(source, sink) << '\n';
    }
}