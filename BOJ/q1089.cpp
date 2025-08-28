#include <iostream>

const int B[10] = { 1168, 14043, 3096, 1560, 13842, 1584, 1072, 14040, 1040, 1552 };

int N;
char S[5][40];

int main() {
	std::cin >> N;
	(std::cout << std::fixed).precision(15);
	for (int i = 0; i < 5; ++i) std::cin >> S[i];
	long double ret = 0;
	for (int i = 0, l = 0, digits, cnt, sum; i < N; ++i, l += 4) {
		ret *= 10;
		digits = 0;
		for (int j = 0; j < 5; ++j) {
			if (S[j][l + 3] == '#') {
				std::cout << -1;
				return 0;
			}
			for (int k = 0; k < 3; ++k) {
				if (S[j][l + k] == '#') {
					int b = j * 3 + k;
					for (int d = 0; d < 10; ++d) {
						if (B[d] & 1 << b) {
							digits |= 1 << d;
						}
					}
				}
			}
		}
		cnt = sum = 0;
		for (int d = 0; d < 10; ++d, digits >>= 1) {
			if (~digits & 1) {
				cnt++;
				sum += d;
			}
		}
		if (cnt == 0) {
			std::cout << -1;
			return 0;
		}
		ret += (long double)sum / cnt;
	}
	std::cout << ret;
}