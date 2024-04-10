#include <iostream>

int P, T, A[20], S;

int main() {
	std::cin >> P;
	while (P--) {
		S = 0;
		std::cin >> T >> A[0];
		for (int i = 1, l, r, m, k; i < 20; ++i) {
			std::cin >> A[i];
			l = 0; r = i;
			while (l < r) {
				m = l + r >> 1;
				if (A[m] > A[i]) r = m;
				else l = m + 1;
			}
			S += i - r;
			k = A[i];
			for (int j = i; j > r; --j) A[j] = A[j - 1];
			A[r] = k;
		}
		std::cout << T << ' ' << S << '\n';
	}
}