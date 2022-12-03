#include <iostream>

int main() {
	int h, w, r = 0;
	std::string s;
	std::cin >> h >> w;
	for (int i = 0; i < h; ++i) {
		std::cin >> s;
		for (const char& c : s)
			if (c == '#') r++;
	}
	std::cout << r;
}