#include <iostream>

int main() {
	int N;
	std::string s;
	bool o = false, x = false;
	std::cin >> N >> s;
	for (const char& c : s) {
		if (c == 'o') o = 1;
		if (c == 'x') x = 1;
	}
	std::cout << (o && !x ? "Yes" : "No");
}