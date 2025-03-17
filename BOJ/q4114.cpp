#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

const int LEN = 1000;

int N, K;
int X[LEN], T[LEN], S[LEN], C[LEN];
std::vector<int> g[LEN];

void solve() {
	int ret = N, t = 0;
	memset(X, 0, sizeof X);
	memset(S, 0, sizeof S);
	for (int i = 0; i < N; ++i) g[i].clear();
	std::queue<int> q;
	for (int u = 0, k; u < N; ++u) {
		std::cin >> T[u] >> C[u];
		S[u] += T[u];
		t += T[u];
		for (int j = 0, v; j < C[u]; ++j) {
			std::cin >> v;
			g[u].push_back(v);
			S[v] += T[u];
		}
	}
	for (int u = 0; u < N; ++u) {
		if (S[u] < K) {
			X[u] = 1;
			q.push(u);
		}
	}
	while (q.size()) {
		int u = q.front(); q.pop();
		ret--;
		t -= T[u];
		for (const int& v : g[u]) {
			C[v] -= 1;
			if (X[v]) continue;
			S[v] -= T[u];
			if (S[v] < K) {
				X[v] = 1;
				q.push(v);
			}
		}
	}
	std::cout << ret << ' ' << t << '\n';
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	while (1) {
		std::cin >> N >> K;
		if (!N) break;
		solve();
	}
}