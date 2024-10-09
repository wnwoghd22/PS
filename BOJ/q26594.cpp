#include <iostream>

int main() {
	std::string s;
	std::cin >> s;
	char c = s[0];
	int N = 1;
	for (int i = 1; i < s.length(); ++i) {
		if (s[i] != c) break;
		N++;
	}
	std::cout << N;
} 