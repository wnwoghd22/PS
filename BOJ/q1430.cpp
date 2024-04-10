#include <iostream>
#include <vector>
#include <queue>

const int LEN = 51;

int N, R, D, X, Y;

int x[LEN], y[LEN];
bool visited[LEN];
int depth[LEN];

std::vector<int> graph[LEN];
int d[LEN];

int main() {
	std::cin >> N >> R >> D >> X >> Y;

	x[0] = X; y[0] = Y;
	for (int i = 1; i <= N; ++i) std::cin >> x[i] >> y[i];
	
	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j <= N; ++j) {
			if ((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) <= R * R) {
				graph[i].push_back(j);
				graph[j].push_back(i);
			}
		}
	}
	std::queue<int> q;
	q.push(0);
	visited[0] = 1;
	while (q.size()) {
		int u = q.front(); q.pop();
		for (const int& v : graph[u]) {
			if (visited[v]) continue;
			visited[v] = 1;
			depth[v] = depth[u] + 1;
			++d[depth[v]];
			q.push(v);
		}
	}
	double sum = 0;
	double eff = 1;
	for (int i = 1; i <= 50; ++i, eff /= 2) sum += d[i] * eff;
	std::cout << sum * D;
}