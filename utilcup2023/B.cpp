#include <iostream>

int n, m;
std::string s;
std::string t;

int main() {
	std::cin >> s;
	std::cin >> n;
	while (n--) {
		std::cin >> t;
		if (t >= s) ++m;
	}
	std::cout << m;
}