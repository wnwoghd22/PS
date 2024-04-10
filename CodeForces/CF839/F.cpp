#include <iostream>
#include <vector>
#include <queue>

std::string p[100][30];
int N, M, K;
std::vector<int> graph[100];
int incoming[100];
bool visited[100];

void compare(int a, int b) {
	int diff = 0, x, y;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (p[a][i][j] != p[b][i][j]) {
				diff++;
				x = i, y = j;
			}
		}
	}
	if (diff == 1) {
		if (p[a][x][y] != p[a][x][y - 1]) {
			graph[a].push_back(b);
			incoming[b]++;
		}
		else {
			graph[b].push_back(a);
			incoming[a]++;
		}
	}
}
void topological_sort() {
	std::queue<int> q;

	for (int i = 0; i < K; ++i) {
		if (!incoming[i]) {
			q.push(i);
		}
	}

	while (!q.empty()) {
		int v = q.front(); q.pop();
		std::cout << v << ' ';
		for (const int& u : graph[v]) {
			if (!--incoming[u]) {
				q.push(u);
			}
		}
	}
}
 
int main() {
	std::cin >> N >> M >> K;
	K++;
	for (int i = 0; i < K; ++i) {
		for (int r = 0; r < N; ++r)
			std::cin >> p[i][r];
	}
	for (int i = 0; i < K; ++i) {
		for (int j = i + 1; j < K; ++j)
			compare(i, j);
	}
	topological_sort();
}