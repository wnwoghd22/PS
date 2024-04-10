#include <iostream>

int main() {
	int result = 0, x;
	std::string s;
	for (int i = 0; i < 4; ++i) {
		std::cin >> s >> x;
		if (s == "Stair") result += x * 17;
		if (s == "Es") result += x * 21;
	}
	std::cout << result;
}