#include <iostream>

int count;
int button[10];
int N;

void dfs(int current, int depth) {
	if (depth >= 1) count = std::min(count, abs(N - current) + depth);
	if (depth == 6) return;

	for (int i = 0; i < 10; ++i) if (!button[i]) dfs(current * 10 + i, depth + 1);
}

int main() {
	int M;
	std::cin >> N >> M;
	while (M--) {
		int i;
		std::cin >> i;
		button[i] = true;
	}

	count = abs(N - 100);
	dfs(0, 0);

	std::cout << count;
}