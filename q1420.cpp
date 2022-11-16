#include <iostream>
#include <vector>
#include <queue>
#include <map>

const int MAX = 20001;
const int INF = 1e9;
const int OUT = 10000;

int N, M, source, sink;
std::string map[100];
std::map<int, int> c[MAX], f[MAX];
int work[MAX], level[MAX];
std::vector<int> A[MAX];
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
    std::cin >> N >> M;

    for (int i = 0; i < N; ++i) std::cin >> map[i];

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            char k = map[i][j];
            if (k == '#') continue;
            int node = i * M + j + 1;
            if (k == 'K') source = node + OUT;
            if (k == 'H') sink = node;
            A[node + OUT].push_back(node);
            A[node].push_back(node + OUT);
            c[node + OUT][node] = 0;
            c[node][node + OUT] = 1;
            f[node + OUT][node] = 0;
            f[node][node + OUT] = 0;

            for (int d = 0; d < 4; ++d) {
                int di = i + dx[d], dj = j + dy[d];
                int dn = M * dx[d] + dy[d];

                if (di < 0 || di >= N || dj < 0 || dj >= M) continue;

                if (map[di][dj] != '#') {
                    A[node + OUT].push_back(node + dn);
                    A[node + dn].push_back(node + OUT);
                    c[node + dn][node + OUT] = 0;
                    c[node + OUT][node + dn] = INF;
                    f[node + dn][node + OUT] = 0;
                    f[node + OUT][node + dn] = 0;

                    A[node + dn + OUT].push_back(node);
                    A[node].push_back(node + dn + OUT);
                    c[node][node + dn + OUT] = 0;
                    c[node + dn + OUT][node] = INF;
                    f[node][node + dn + OUT] = 0;
                    f[node + dn + OUT][node] = 0;
                }
            }
        }
    }

    int result = dinic(source, sink);
    std::cout << (result > 4 ? -1 : result);
}