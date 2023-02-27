#include <iostream>
#include <algorithm>

int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }
int N, R, A[50];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	std::sort(A, A + N);
	for (int i = 0; i < N - 1; ++i) {
		if (gcd(A[i], A[i + 1]) != 1) {
			bool flag = true;
			for (int k = A[i] + 1; k < A[i + 1]; ++k) {
				if (gcd(A[i], k) == 1 && gcd(k, A[i + 1]) == 1) {
					++R;
					flag = false;
					break;
				}
			}
			if (flag) R += 2;
		}
	}
	std::cout << R;
}