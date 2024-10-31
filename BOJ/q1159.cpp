#include <iostream>

int N, x, C[26];
char S[31];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> S;
		x = std::max(x, ++C[S[0] - 'a']);
	}
	if (x >= 5) {
		for (int i = 0; i < 26; ++i) {
			if (C[i] >= 5) {
				std::cout << (char)(i + 'a');
			}
		}
	}
	else std::cout << "PREDAJA";
}