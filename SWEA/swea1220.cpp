#include <iostream>

int N, map[100][100];
int sp, stack[100];

int check_col(int y) {
	sp = 0;
	int cur;
	for (int x = 0; x < N; ++x) {
		cur = map[x][y];
		if (cur == 1) {
			stack[sp++] = 1;
			continue;
		}
		if (cur == 2) {
			if (!sp || stack[sp - 1] == 3) continue;
			else {
				while (sp && stack[sp - 1] != 3) --sp;
				stack[sp++] = 3;
			}
		}
	}
	while (sp && stack[sp - 1] != 3) --sp;
	return sp;
}

int solve() {
	int result = 0;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			std::cin >> map[i][j];
	for (int y = 0; y < N; ++y) result += check_col(y);

	return result;
}

int main() {
	for (int t = 1; t <= 10; ++t) std::cout << '#' << t << ' ' << solve() << '\n';
}