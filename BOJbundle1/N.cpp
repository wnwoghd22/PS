#include <iostream>

int N, H0, H1, S, R;

int main() {
	std::cin >> N >> H0;
	S = H0;
	R = H0 + 2 * N;
	while (--N) {
		std::cin >> H1;
		S += H1;
		R += abs(H1 - H0);
		H0 = H1;
	}
	R += H0;
	std::cout << R + 2 * S;
}