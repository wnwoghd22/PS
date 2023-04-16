#include <iostream>

int N;
char S[2001];

int main() {
	std::cin >> N >> S;
	for (int i = 0; i < N - 1; ++i) {
		int false_rate = 0;
		for (int j = 0; j <= i; ++j) {
			if (S[j] != S[N - i - 1 + j])
				++false_rate;
		}
		if (false_rate == 1) {
			std::cout << "YES";
			return 0;
		}
	}
	std::cout << "NO";
}