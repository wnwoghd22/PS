#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

int H, W, mex[20][20][20][20];
char map[20][21];

int f(int l, int r, int u, int d) {
	if (r < l || d < u) return 0;
	int& ref = mex[l][r][u][d];
	if (~ref) return ref;
	ref = 0;
	bool visited[100];
	for (int i = 0; i < 100; ++i) visited[i] = 0;
	for (int i = l; i <= r; ++i) {
		for (int j = u; j <= d; ++j) {
			if (map[j][i] != 'X') {
				int lu = f(l, i - 1, u, j - 1);
				int ru = f(i + 1, r, u, j - 1);
				int ld = f(l, i - 1, j + 1, d);
				int rd = f(i + 1, r, j + 1, d);
				visited[lu ^ ru ^ ld ^ rd] = 1;
			}
		}
	}
	for (int i = 0; i < 100; ++i) {
		if (!visited[i]) {
			ref = i;
			break;
		}
	}
	return ref;
}

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> H >> W;
	memset(mex, -1, sizeof mex);
	for (int i = 0; i < H; ++i) std::cin >> map[i];
	std::cout << (f(0, W - 1, 0, H - 1) ? "First" : "Second");
}