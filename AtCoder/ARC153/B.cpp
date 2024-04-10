#include <iostream>

std::string grid[500'000];
bool r = false;
int H, W, Q, a, b, zero_h = 0, zero_w = 0;

int main() {
	std::cin >> H >> W;
	for (int i = 0; i < H; ++i) std::cin >> grid[i];
	std::cin >> Q;
	while (Q--) {
		std::cin >> a >> b;
		if (zero_h < a) zero_h = a - 1 - zero_h;
		else zero_h = H - zero_h + a - 1;

		if (zero_w < b) zero_w = b - 1 - zero_w;
		else zero_w = W - zero_w + b - 1;
		r = !r;
	}
	if (r) {
		for (int i = 0; i < H; ++i) {
			for (int j = 0; j < W; ++j) {
				std::cout << grid[(H + zero_h - i) % H][(W + zero_w - j) % W];
			}
			std::cout << '\n';
		}
	}
	else {
		for (int i = 0; i < H; ++i) {
			for (int j = 0; j < W; ++j) {
				std::cout << grid[(H - zero_h + i) % H][(W - zero_w + j) % W];
			}
			std::cout << '\n';
		}
	}
}