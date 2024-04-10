#include <iostream>
#include <algorithm>

int count[26];

int main() {
	int N, result = 100'000;
	std::string s;
	std::cin >> N >> s;
	for (const char& c : s) count[c - 'A'] += 1;
	std::cout << std::min({ count[0], count[2], count[7], count[8], count[17] });
}