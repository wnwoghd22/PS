#include <iostream>
#include <vector>

const int INF = 1e9;
std::vector<std::pair<int, int>> pos_chicken;
std::vector<std::pair<int, int>> pos_home;
int N, M;

int get_distance(int visited) {
	if (!visited) return INF;

	int result = 0;
	for (const auto& h : pos_home) {
		int current = INF;
		for (int i = 0; i < pos_chicken.size(); ++i) {
			if (1 << i & visited) {
				std::pair<int, int>& c = pos_chicken[i];
				current = std::min(abs(h.first - c.first) + abs(h.second - c.second), current);
			}
		}
		result += current;
	}
	return result;
}

int dfs(int index = 0, int visited = 0, int depth = 0) {
	int result = get_distance(visited);

	if (depth == M) return result;

	for (int i = index; i < pos_chicken.size(); ++i) {
		result = std::min(result, dfs(i + 1, visited | 1 << i, depth + 1));
	}
	return result;
}

int main() {
	std::cin >> N >> M;

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			int k;
			std::cin >> k;
			if (k == 1) pos_home.push_back({ i, j });
			if (k == 2) pos_chicken.push_back({ i, j });
		}
	}
	std::cout << dfs();
}