#include <iostream>
#include <queue>
#include <cstring>

const int MAX = 10'001;
std::vector<int> graph[MAX];
bool visited[MAX];

int bfs(int v) {
	memset(visited, 0, sizeof visited);
	std::queue<int> q;
	int result = 1;
	visited[v] = true;
	q.push(v);

	while (!q.empty()) {
		v = q.front(); q.pop();

		for (const int& u : graph[v]) {
			if (!visited[u]) {
				++result;
				visited[u] = true;
				q.push(u);
			}
		}
	}
	return result;
}

int main() {
	int N, M, _size = 0;
	std::cin >> N >> M;
	while (M--) {
		int A, B;
		std::cin >> A >> B;
		graph[B].push_back(A);
	}
	std::vector<int> container;
	for (int i = 1; i <= N; ++i) {
		int current = bfs(i);
		if (current > _size) {
			_size = current;
			container.clear();
			container.push_back(i);
		}
		else if (current == _size) container.push_back(i);
	}
	for (const int& i : container) std::cout << i << ' ';
}