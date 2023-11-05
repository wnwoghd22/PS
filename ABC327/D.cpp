#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>

const int LEN = 2e5 + 1;

std::vector<int> graph[LEN];
int visited[LEN];

bool bfs(int idx) {
	int u, color; bool result = true;
	std::queue<int> q;
	visited[idx] = 1;
	q.push(idx);

	while (q.size()) {
		u = q.front(); q.pop(); color = visited[u];
		for (const int& v : graph[u]) {
			if (!visited[v]) {
				visited[v] = color == 1 ? 2 : 1;
				q.push(v);
			}
			else if (visited[v] == color) result = false;
		}
	}
	return result;
}

int A[LEN], B[LEN];

int main() {
	int K, V, E, u, v, result = 1;
	std::cin >> V >> E;

	for (int i = 1; i <= E; ++i) std::cin >> A[i];
	for (int i = 1; i <= E; ++i) std::cin >> B[i];
	for (int i = 1; i <= E; ++i) {
		if (A[i] == B[i]) {
			std::cout << "No";
			return 0;
		}
		graph[A[i]].push_back(B[i]);
		graph[B[i]].push_back(A[i]);
	}

	for (v = 1; v <= V; ++v) {
		if (!visited[v] && !bfs(v)) {
			result = false;
			break;
		}
	}
	std::cout << (result ? "Yes" : "No") << '\n';
}