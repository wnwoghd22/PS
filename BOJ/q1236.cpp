#include <iostream>

char S[51];
int R, C, r[51], c[51], x, y;

int main() {
	std::cin >> R >> C;
	for (int i = 0; i < R; ++i) {
		std::cin >> S;
		for (int j = 0; j < C; ++j) {
			if (S[j] == 'X') {
				r[i] |= 1;
				c[j] |= 1;
			}
		}
	}
	for (int i = 0; i < R; ++i) x += !r[i];
	for (int i = 0; i < C; ++i) y += !c[i];
	std::cout << std::max(x, y);
}