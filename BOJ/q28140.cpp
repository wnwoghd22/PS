#include <iostream>

const int LEN = 1e6 + 1;
char S[LEN];
int N, Q, pre[LEN], next[LEN];

int main() {
	std::cin >> N >> Q >> S;

	// preprocess
	for (int i = N - 1, j = N; i >= 0; --i) {
		next[i] = j;
		if (S[i] == 'R') j = i;
	}
	for (int i = 0, j = -1; i < N; ++i) {
		pre[i] = j;
		if (S[i] == 'B') j = i;
	}
	for (int i = 0; i < N; ++i) std::cout << next[i] << ' '; std::cout << '\n';
	for (int i = 0; i < N; ++i) std::cout << pre[i] << ' '; std::cout << '\n';

	for (int i = 0, l, r, a, b, c, d; i < Q; ++i) {
		std::cin >> l >> r;
		if (next[l] >= N) {
			std::cout << "-1\n";
			continue;
		}
		if (S[l] == 'R') a = l, b = next[l];
		else {
			a = next[l];
			if (next[a] >= N) {
				std::cout << "-1\n";
				continue;
			}
			b = next[a];
		}

		if (pre[r] < 0) {
			std::cout << "-1\n";
			continue;
		}
		if (S[r] == 'B') d = r, c = pre[r];
		else {
			d = pre[r];
			if (pre[d] < 0) {
				std::cout << "-1\n";
				continue;
			}
			c = pre[d];
		}

		if (b > c) {
			std::cout << "-1\n";
			continue;
		}
		std::cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
	}
}