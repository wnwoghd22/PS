#include <iostream>

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		std::string S;
		std::cin >> S;
		std::cout << S[0] - '0' + S[2] - '0' << '\n';
	}
}