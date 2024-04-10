#include <iostream>

typedef long long ll;
const int LEN = 1e6 + 1;

int T, N;
ll S[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	for (int i = 1; i < LEN; ++i) {
		for (int j = i; j < LEN; j += i)
			S[j] += i;
		S[i] += S[i - 1];
	}
	std::cin >> T;
	while (T--) {
		std::cin >> N;
		std::cout << S[N] << '\n';
	}
}