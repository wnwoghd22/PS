#include <iostream>
#include <string>

char A[5][6];
std::string r = "$$$$$", c = "$$$$$";
std::string R, C;
int bit[5];

int N;
bool f(int i) {
	if (i == N) {
		for (int j = 0; j < N; ++j)
			if (bit[j] ^ 7) return 0;
		return 1;
	}
	char c1, c2;
	if (R[i] == 'A') c1 = 'B', c2 = 'C';
	if (R[i] == 'B') c1 = 'A', c2 = 'C';
	if (R[i] == 'C') c1 = 'A', c2 = 'B';
	for (int i1 = 0; i1 < N - 2; ++i1) {
		if (bit[i1] & 1 << (R[i] - 'A')) continue;
		if (!bit[i1] && R[i] != C[i1]) continue;
		if (!bit[i1]) c[i1] = R[i];
		bit[i1] |= 1 << (R[i] - 'A');
		A[i][i1] = R[i];
		for (int i2 = i1 + 1; i2 < N; ++i2) {
			for (int i3 = i1 + 1; i3 < N; ++i3) {
				if (i2 == i3) continue;
				if (bit[i2] & 1 << (c1 - 'A')) continue;
				if (bit[i3] & 1 << (c2 - 'A')) continue;
				if (!bit[i2] && c1 != C[i2]) continue;
				if (!bit[i3] && c2 != C[i3]) continue;

				if (!bit[i2]) c[i2] = c1;
				bit[i2] |= 1 << (c1 - 'A');
				A[i][i2] = c1;

				if (!bit[i3]) c[i3] = c2;
				bit[i3] |= 1 << (c2 - 'A');
				A[i][i3] = c2;

				if (f(i + 1)) return 1;

				bit[i2] &= ~(1 << (c1 - 'A'));
				if (!bit[i2]) c[i2] = '$';
				A[i][i2] = 0;

				bit[i3] &= ~(1 << (c2 - 'A'));
				if (!bit[i3]) c[i3] = '$';
				A[i][i3] = 0;
			}
		}
		bit[i1] &= ~(1 << (R[i] - 'A'));
		if (!bit[i1]) c[i1] = '$';
		A[i][i1] = 0;
	}
	return 0;
}

int main() {
	std::cin >> N >> R >> C;
	if (f(0)) {
		std::cout << "Yes\n";
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j)
				if (!A[i][j]) A[i][j] = '.';
			std::cout << A[i] << '\n';
		}
	}
	else std::cout << "No";
}