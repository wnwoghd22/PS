#include <iostream>

const int LEN = 2'000'000;
int N, dq[LEN], h = LEN / 2, t = LEN / 2;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0, q, x; i < N; ++i) {
		std::cin >> q;
		if (q == 1) std::cin >> x, dq[h--] = x;
		if (q == 2) std::cin >> x, dq[++t] = x;
		if (q == 3) std::cout << (h < t ? dq[++h] : -1) << '\n';
		if (q == 4) std::cout << (h < t ? dq[t--] : -1) << '\n';
		if (q == 5) std::cout << t - h << '\n';
		if (q == 6) std::cout << (h == t) << '\n';
		if (q == 7) std::cout << (h < t ? dq[h + 1] : -1) << '\n';
		if (q == 8) std::cout << (h < t ? dq[t] : -1) << '\n';
	}
}