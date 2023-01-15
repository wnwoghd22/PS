#include <iostream>

int main() {
	int N;
	std::string s;
	std::cin >> N;
	std::cin >> s;
	for (int i = 1, j; i < N; ++i) {
		for (j = 0; j + i < N; ++j) {
			if (s[j] == s[i + j]) break;
		}
		std::cout << j << '\n';
	}
}