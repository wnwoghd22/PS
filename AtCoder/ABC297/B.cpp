#include <iostream>

int main() {
	int k;
	int ri = 0, r[2];
	int bi = 0, b[2];
	std::string s;
	std::cin >> s;
	for (int i = 0; i < 8; ++i) {
		char c = s[i];
		if (c == 'K') k = i;
		if (c == 'R') r[ri++] = i;
		if (c == 'B') b[bi++] = i;
	}
	if (k > r[0] && k < r[1] && ((b[0] ^ b[1]) & 1))
		std::cout << "Yes";
	else std::cout << "No";
}