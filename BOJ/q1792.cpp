#include <iostream>

const int LEN = 50'001;
int N, A, B, D, S[LEN] = { 0, 1, };

void init() {
	for (int i = 1; i < LEN; ++i) {
		if (S[i]) {
			for (int j = i << 1; j < LEN; j += i)
				S[j] -= S[i];
		}
		S[i] += S[i - 1];
	}
}

__int64 f(int a, int b) {
	__int64 c = 0;
	for (__int64 i = 1, j; i <= std::min(a, b); i = j + 1) {
		j = std::min(a / (a / i), b / (b / i));
		c += (a / i) * (b / i) * (S[j] - S[i - 1]);
	}
	return c;
}

int main() {
	init();
	std::cin >> N;
	while (N--) {
		std::cin >> A >> B >> D;
		std::cout << f(A / D, B / D) << '\n';
	}
}