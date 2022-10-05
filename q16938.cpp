#include <iostream>

int N, L, R, X;
int A[15];
int count;

void check(int visited) {
	int max = 0, min = 1'000'001;
	int sum = 0;
	for (int i = 0; i < 15; ++i) {
		if (1 << i & visited) {
			max = std::max(max, A[i]);
			min = std::min(min, A[i]);
			sum += A[i];
		}
	}
	if (max - min >= X && L <= sum && sum <= R) ++count;
}

void dfs(int index = 0, int visited = 0, int depth = 0) {
	if (depth > 1) check(visited);

	for (int i = index; i < N; ++i)
		dfs(i + 1, visited | 1 << i, depth + 1);
}

int main() {
	std::cin >> N >> L >> R >> X;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	dfs();
	std::cout << count;
}