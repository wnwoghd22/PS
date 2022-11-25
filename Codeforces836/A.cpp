#include <iostream>
#include <algorithm>

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		std::string s;
		std::cin >> s;
		std::cout << s;
		std::reverse(s.begin(), s.end());
		std::cout << s << '\n';
	}
}