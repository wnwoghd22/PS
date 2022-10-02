#include <iostream>
#include <vector>
#include <algorithm>

const int MAX = 100'000;
int M, result = 0;

int info_len[MAX];
int info[MAX][20];
int depth[MAX][10];

int main() {
	int N; // garbage
	std::cin >> N >> M;
	for (int i = 0; i < M; ++i) std::cin >> info_len[i];
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < info_len[i]; ++j)
			std::cin >> info[i][j];

	for (int i = 1; i < M; ++i) {
		for (int j = 0; j < info_len[i]; j += 2) {
			for (int k = 0; k < info_len[i - 1]; k += 2) {
				if (info[i][j + 1] >= info[i - 1][k] && info[i][j] <= info[i - 1][k + 1]) {
					depth[i][j / 2] = std::max(depth[i][j / 2], depth[i - 1][k / 2] + 1);
				}
			}
		}
	}
	int max = *std::max_element(depth[M - 1], depth[M - 1] + 10);

	std::cout << (max == M - 1 ? "YES" : "NO");
}
