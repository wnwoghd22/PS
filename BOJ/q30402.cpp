#include <iostream>

int main() {
	char c;
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			std::cin >> c;
			switch (c) {
			case 'w':
				std::cout << "chunbae";
				return 0;
			case 'b':
				std::cout << "nabi";
				return 0;
			case 'g':
				std::cout << "yeongcheol";
				return 0;
			default:
				break;
			}
		}
	}
}