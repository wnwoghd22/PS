#include <iostream>

int main() {
	int index = -1;
	std::string S, T;
	std::cin >> S >> T;
	for (int i = 0; i < S.length(); ++i) {
		if (S[i] != T[i]) {
			index = i + 1;
			break;
		}
	}
	if (!~index) index = T.length();

	std::cout << index;
}