#include <iostream>

std::string pi = "314159265358979323846264338327";

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		std::string s;
		std::cin >> s;
		int i = 0;
		for (int j = 0; j < s.length(); ++j) {
			if (s[j] == pi[j]) ++i;
			else break;
		}
		std::cout << i << '\n';
	}
}