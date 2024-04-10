#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

const int LEN = 2000;
int map[LEN][LEN];
int lu[LEN][LEN], ru[LEN][LEN], ld[LEN][LEN], rd[LEN][LEN];
int R, C, result;

int main() {
	scanf("%d %d", &R, &C);

	for (int r = 1; r <= R; ++r)
		for (int c = 1; c <= C; ++c)
			scanf("%1d", &map[r][c]);

	for (int r = R; r >= 1; --r) {
		for (int c = 1; c <= C; ++c) {
			if (map[r][c]) {
				ld[r][c] = ld[r + 1][c - 1] + 1;
				rd[r][c] = rd[r + 1][c + 1] + 1;
			}
		}
	}
	for (int r = 1; r <= R; ++r) {
		for (int c = 1; c <= C; ++c) {
			if (map[r][c]) {
				lu[r][c] = lu[r - 1][c - 1] + 1;
				ru[r][c] = ru[r - 1][c + 1] + 1;
			}
		}
	}
	for (int r = 1; r <= R; ++r) {
		for (int c = 1; c <= C; ++c) {
			for (int k = 1; k <= std::min(ld[r][c], rd[r][c]); ++k) {
				int d = r + 2 * (k - 1);
				if (map[d][c] && std::min(lu[d][c], ru[d][c]) >= k)
					result = std::max(result, k);
			}
			for (int k = 1; k <= std::min(ru[r][c], rd[r][c]); ++k) {
				int l = c + 2 * (k - 1);
				if (map[r][l] && std::min(lu[r][l], ld[r][l]) >= k)
					result = std::max(result, k);

			}
		}
	}

	std::cout << result;
}