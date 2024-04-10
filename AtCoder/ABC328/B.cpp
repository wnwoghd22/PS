#include <iostream>

int N, D[101], C;

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> D[i];
	for (int i = 1; i <= N; ++i) {
		int mm = i, d = mm % 10; mm /= 10;
		bool fm = 1;
		while (mm) {
			if (mm % 10 != d) {
				fm = false;
				break;
			}
			mm /= 10;
		}
		if (!fm) continue;
		for (int j = 1; j <= D[i]; ++j) {
			int dd = j;
			if (dd % 10 != d) continue;
			dd /= 10;
			bool fd = 1;
			while (dd) {
				if (dd % 10 != d) {
					fd = false;
					break;
				}
				dd /= 10;
			}
			if (!fd) continue;
			C++;
		}
	}
	std::cout << C;
}