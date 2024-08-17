#include <iostream>
#include <algorithm>
#include <cstring>

const int LEN = 1001;

struct Log {
	int t, a, b;
	bool operator<(const Log& o) const {
		return t < o.t;
	}
} logs[LEN * 10];
bool infected[LEN];
bool check[LEN];
int node[LEN];
int N, M, K;

int simulate(int k) {
	memset(check, 0, sizeof check);
	check[k] = 1;
	int cnt = 1;
	for (int i = 0; i < M; ++i) {
		int u = logs[i].a;
		int v = logs[i].b;
		if (check[u]) {
			if (!infected[v]) return 0;
			if (!check[v]) {
				cnt++;
				check[v] = 1;
			}
		}
	}
	return cnt == K;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M >> K;
	for (int i = 0; i < K; ++i) {
		std::cin >> node[i];
		infected[node[i]] = 1;
	}
	for (int i = 0; i < M; ++i) {
		std::cin >> logs[i].t >> logs[i].a >> logs[i].b;
	}
	std::sort(logs, logs + M);
	for (int i = 0; i < K; ++i) {
		if (simulate(node[i])) {
			std::cout << node[i];
			break;
		}
	}
}