#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

int pos[11], x;

int main() {
	freopen("input.txt", "r", stdin);
	for (int i = 0; i < 2047; ++i) {
		for (int j = 0; j < 11; ++j) {
			std::cin >> x;
			pos[j] ^= x;
		}
	}
	for (int j = 0; j < 11; ++j) std::cout << pos[j] << ' ';
}