#include <iostream>

const int LEN = 101;

int N, M, D;
char map[LEN][LEN];

int main() {
	std::cin >> N >> M >> D;
	for (int i = 0; i < N; ++i) std::cin >> map[i];
	int ret = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0, x = 0; j < M; ++j) {
			if (map[i][j] == '.') x++;
			else x = 0;
			if (x >= D) ret++;
		}
	}
	for (int j = 0; j < M; ++j) {
		for (int i = 0, x = 0; i < N; ++i) {
			if (map[i][j] == '.') x++;
			else x = 0;
			if (x >= D) ret++;
		}
	}
	std::cout << ret;
}