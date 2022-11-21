#include <iostream>

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		std::string s;
		int i;
		int result = 0;
		std::cin >> i >> s;
		for (const char& c : s) {
			result = std::max(result, c - 'a' + 1);
		}
		std::cout << result << '\n';
	}
}