#include <iostream>

int N, M, V;
int G, C, I[32];

void solve(int tc) {
	std::cin >> M >> V;
	G = C = 0;
	int cnt = (M - 1) / 2;
	for (int i = 1, g, c; i <= cnt; ++i) {
		std::cin >> g >> c;
		G |= g << i;
		C |= c << i;
	}
	for (int i = 1; i <= (M + 1) / 2; ++i) {
		std::cin >> I[i + cnt];
	}
	int ret = -1;
	for (int b = 0; b < (1 << cnt + 1) - 1; b += 2) {
		if ((G ^ b) & ~C) continue;
		for (int i = cnt; i > 0; --i) {
			I[i] = b & (1 << i) ? 
				I[i * 2] & I[i * 2 + 1] : 
				I[i * 2] | I[i * 2 + 1];
		}
		if (I[1] != V) continue;
		int cur = 0;
		int i = G ^ b;
		while (i) {
			i -= i & -i;
			cur++;
		}
		if (!~ret || cur < ret) ret = cur;
	}

	std::cout << "Case #" << tc << ": ";
	if (~ret) std::cout << ret << '\n';
	else std::cout << "IMPOSSIBLE\n";
}

int main() {
	std::cin >> N;
	for (int tc = 1; tc <= N; ++tc) solve(tc);
}