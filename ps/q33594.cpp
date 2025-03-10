#include <iostream>
#include <vector>
#include <queue>

typedef long long ll;

const int LEN = 1001;

std::vector<int> g[LEN];
int N, X[LEN], Y[LEN], R[LEN], C[LEN];
ll sq(ll x) { return x * x; }

bool bfs(int x) {
    int u, c, b = 0, w = 0, ret = 1;
    std::queue<int> q;
    C[x] = 1;
    q.push(x);

    while (!q.empty()) {
        u = q.front(); q.pop();
        C[u] == 1 ? b++ : w++;
        for (const int& v : g[u]) {
            if (!C[v]) {
                C[v] = C[u] == 1 ? 2 : 1;
                q.push(v);
            }
            else if (C[v] == C[u]) ret = 0;
        }
    }
    return ret && b != w;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> X[i] >> Y[i] >> R[i];
	for (int i = 1; i < N; ++i) {
		for (int j = i + 1; j <= N; ++j) {
			if (sq(X[j] - X[i]) + sq(Y[j] - Y[i]) == sq(R[j] + R[i])) {
				g[i].push_back(j);
				g[j].push_back(i);
			}
		}
	}
    int ret = 0;
    for (int i = 1; i <= N; ++i) {
        if (!C[i]) ret |= bfs(i);
    }
    std::cout << (ret ? "YES" : "NO");
}