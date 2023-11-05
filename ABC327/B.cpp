#include <iostream>

typedef long long ll;

ll N, A, P;

int main() {
	std::cin >> N;
	A = 1;
	while (1) {
		P = 1;
		for (int i = 0; i < A; ++i) P *= A;
		if (P == N) {
			std::cout << A;
			return 0;
		}
		if (P > N) break;
		A++;
	}
	std::cout << -1;
}