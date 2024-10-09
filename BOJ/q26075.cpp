#include <iostream>

typedef long long int ll;
const int LEN = 100'000;

int S[LEN], T[LEN];

int main() {
	int N, M; ll x = 0, y = 0, odd = 0; char c;
	std::cin >> N >> M;

	for (int i = 0, j = 0; i < N + M; ++i) {
		std::cin >> c;
		if (c == '1') S[j++] = i;
	}
	for (int i = 0, j = 0; i < N + M; ++i) {
		std::cin >> c;
		if (c == '1') T[j++] = i;
	}
	for (int i = 0; i < M; ++i) {
		ll d = abs(S[i] - T[i]);
		x += d / 2, y += d / 2, odd += d & 1;
	}
	while (odd--) x > y ? ++y : ++x;

	std::cout << x * x + y * y;
}