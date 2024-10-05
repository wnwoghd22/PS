#include <iostream>

const int LEN = 101;
bool gazi[LEN];
int N, M, K;
char c;

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		std::cin >> c;
		gazi[i] = c == 'W';
	}
	bool result = 0;
	std::cin >> M >> K;
	while (M--) {
		bool cur = 1;
		for (int i = 0, j; i < K; ++i) {
			std::cin >> j;
			cur &= gazi[j];
		}
		result |= cur;
	}
	std::cout << (result ? 'W' : 'P');
}