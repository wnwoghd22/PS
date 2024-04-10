#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

const int MAX = 103;
const int INF = 1e9;

int N, sum;
int c[MAX][MAX], f[MAX][MAX];
int work[MAX], level[MAX];
std::vector<int> A[MAX];
int source = 101, sink = 102;

bool bfs(int S, int T, int C) {
    std::fill(level, level + MAX, -1);
    level[S] = 0;

    std::queue<int> q;
    q.push(S);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (const int& u : A[v]) {
            int cap = ~c[v][u] ? c[v][u] : C;
            if (!~level[u] && cap - f[v][u] > 0) {
                level[u] = level[v] + 1;
                q.push(u);
            }
        }
    }
    return ~level[T];
}
int dfs(int here, int target, int flow, const int C) {
    if (here == target) return flow;

    for (int& i = work[here]; i < A[here].size(); ++i) {
        int next = A[here][i];

        int cap = ~c[here][next] ? c[here][next] : C;
        if (level[next] == level[here] + 1 && cap - f[here][next] > 0) {
            int ret = dfs(next, target, std::min(cap - f[here][next], flow), C);

            if (ret > 0) {
                f[here][next] += ret;
                f[next][here] -= ret;

                return ret;
            }
        }
    }

    return 0;
}
int dinic(int S, int T, int C) {
    int totalFlow = 0;
    memset(f, 0, sizeof f);

    while (bfs(S, T, C)) {
        std::fill(work, work + MAX, 0);

        while (1) {
            int flow = dfs(S, T, INF, C);
            if (flow == 0)
                break;
            totalFlow += flow;
        }
    }
    return totalFlow;
}

int binary_search() {
    int l = 1, r = 10000, result = 10000, mid, val;

    while (l <= r) {
        mid = (l + r) / 2;
        val = dinic(source, sink, mid);

        if (val == sum) {
            result = std::min(result, mid);
            r = mid - 1;
        }
        else l = mid + 1;

    }
    return result;
}

int main() {
    std::cin >> N;

    for (int i = 1; i <= N; ++i) {
        std::cin >> c[source][i];
        sum += c[source][i];
        A[source].push_back(i);
        A[i].push_back(source);
        for (int j = 1; j <= N; ++j) {
            A[i].push_back(j + 50);
            A[j + 50].push_back(i);
            c[i][j + 50] = -1;
        }
    }
    for (int i = 1; i <= N; ++i) {
        std::cin >> c[i + 50][sink];
        A[i + 50].push_back(sink);
        A[sink].push_back(i + 50);
    }

    int cap = binary_search();
    dinic(source, sink, cap);

    std::cout << cap << '\n';
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j)
            std::cout << f[i][j + 50] << ' ';
        std::cout << '\n';
    }
}