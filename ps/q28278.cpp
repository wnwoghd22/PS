#include <iostream>

const int LEN = 1'000'000;
int N, S[LEN], sp;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0, q, x; i < N; ++i) {
		std::cin >> q;
		if (q == 1) std::cin >> x, S[sp++] = x;
		if (q == 2) std::cout << (sp ? S[--sp] : -1) << '\n';
		if (q == 3) std::cout << sp << '\n';
		if (q == 4) std::cout << !sp << '\n';
		if (q == 5) std::cout << (sp ? S[sp - 1] : -1) << '\n';
	}
}