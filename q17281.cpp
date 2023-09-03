#include <iostream>

int N;
int A[50][9];
int P[9]; // permutation

int simulate() {
	int score = 0;

	int k = 0;
	for (int i = 0, o, b, h; i < N; ++i) {
		o = 0;
		b = 0;
		while (o < 3) {
			if (A[i][P[k]]) {
				b = b << A[i][P[k]] | 1 << (A[i][P[k]] - 1);
				h = b & ~7;
				while (h) {
					++score;
					h -= h & -h;
				}
				b &= 7;
			}
			else ++o;

			k = (k + 1) % 9;
		}
	}
	return score;
}

int max = 0;
void f(int i, int b) {
	if (b == 511) max = std::max(max, simulate());
	for (int j = 0; j < 9; ++j) {
		if (b & 1 << j) continue;
		P[i] = j;
		f(i + 1 + (i == 2), b | 1 << j);
	}
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < 9; ++j)
			std::cin >> A[i][j];
	}
	f(0, 1);
	std::cout << max;
}