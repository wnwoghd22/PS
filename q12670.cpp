#include <iostream>
#include <vector>
#include <queue>
#include <map>

const int MAX = 3000;
const int INF = 1e9;
const int source = MAX - 2;
const int sink = MAX - 1;

int T, N, M;
char S[51];
int map[52][52];
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

int solve() {
    for (int i = 0; i < MAX; ++i) {
        c[i].clear();
        f[i].clear();
        A[i].clear();
    }

    std::cin >> N >> M;
    for (int i = 0; i <= N + 1; ++i)
        for (int j = 0; j <= M + 1; ++j)
            map[i][j] = 1 << ((i ^ j) & 1);

    for (int i = 0; i < N; ++i) {
        std::cin >> S;
        for (int j = 0; j < M; ++j) {
            if (S[j] == '#') map[i + 1][j + 1] = 1 << (~(i ^ j) & 1);
            if (S[j] == '?') map[i + 1][j + 1] = 3;
        }
    }

    for (int i = 0; i <= N + 1; ++i) {
        for (int j = 0; j <= M + 1; ++j) {
            int node = i * (M + 2) + j; 
            if (map[i][j] == 1) {
                A[source].push_back(node);
                c[source][node] = 4;
                f[source][node] = 0;
            }
            if (map[i][j] == 2) {
                A[node].push_back(sink);
                c[node][sink] = INF;
                f[node][sink] = 0;
            }
            for (int d = 0; d < 4; ++d) {
                int di = i + dx[d], dj = j + dy[d];
                int dn = (M + 2) * dx[d] + dy[d];

                if (di < 0 || di > N + 1 || dj < 0 || dj > M + 1) continue;
                A[node].push_back(node + dn);
                c[node][node + dn] = 1;
                f[node][node + dn] = 0;
            }
        }
    }

    int total = 2 * N * M + 3 * M + 3 * N + 4;
    int max_flow = dinic(source, sink);
    std::cout << total << ' ' << max_flow << '\n';
    return total - max_flow;
}

int main() {
    std::cin >> T;
    for (int t = 1; t <= T; ++t)
        printf("Case #%d: %d\n", t, solve());
}