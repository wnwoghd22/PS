#include <iostream>

const int LEN = 5e5 + 1;
const int INF = 1e9 + 1;

int N, H, sp, i[LEN], h[LEN], answer[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	h[sp] = INF;
	for (int k = 1; k <= N; ++k) {
		std::cin >> H;
		while (H > h[sp]) --sp;
		answer[k] = i[sp];
		++sp;
		h[sp] = H;
		i[sp] = k;
	}
	for (int k = 1; k <= N; ++k) std::cout << answer[k] << ' ';
}