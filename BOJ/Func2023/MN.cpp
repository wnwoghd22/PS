#include <iostream>
#include <vector>

const int LEN = 1e6 + 1;
std::vector<int> graph[LEN];
std::vector<int> stack;
int index[LEN];

void dfs(int u) {
	int i = 1;
	for (const int& v : graph[u]) {
		index[v] = i++;
		dfs(v);
	}
}

int C, M;

int main() {
	std::cin >> C;
	stack.push_back(0);
	for (int i = 1; i <= C; ++i) {
		std::cin >> M; 
		if (M > stack.size()) {
			std::cout << -1;
			return 0;
		}

		while (stack.size() > M) stack.pop_back();
		graph[stack.back()].push_back(i);
		stack.push_back(i);
	}
	dfs(0);
	for (int i = 1; i <= C; ++i) std::cout << index[i] << ' ';
}