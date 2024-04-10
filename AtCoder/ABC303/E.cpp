#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

const int LEN = 2e5 + 1;
int N;
std::vector<int> graph[LEN];
int step[LEN], incoming[LEN], visited[LEN], size[LEN];

std::vector<int> K;
std::queue<int> Q;

int main() {
	std::cin >> N;
	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
		incoming[u]++;
		incoming[v]++;
	}
	for (int i = 1; i <= N; ++i) {
		if (incoming[i] == 1) {
			visited[i] = 1;
			step[i] = 2;
			Q.push(i);
		}
	}
	while (Q.size()) {
		int u = Q.front(); Q.pop();
		size[u] += 1;

		if (step[u] == 0) K.push_back(size[u]);
		
		for (const int& v : graph[u]) {
			if (visited[v]) continue;
			if (step[u]) size[v] += size[u];

			step[v] = (step[u] + 2) % 3;
			if (--incoming[v] == 1) {
				visited[v] = 1;
				Q.push(v);
			}
		}
	}

	int sum = 0;
	for (const int& k : K) sum += k;
	if (sum < N)
		K.push_back(N - sum);
	std::sort(K.begin(), K.end());
	for (const int& k : K) std::cout << k - 1 << ' ';
}