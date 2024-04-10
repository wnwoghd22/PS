#include <iostream>

typedef long double ld;

ld power(ld A, int B) {
	if (B == 1) return A;
	else {
		ld pw = power(A, B / 2);
		return pw * pw * (B % 2 ? A : 1);
	}
}
ld f_p(ld F, int T) { return power(1 + F / 2, T); }
ld f(ld F, int T) { return pow(1 + F / 2, T); }


int main() {
	int N;
	std::cin >> N;

	std::cout << std::fixed;
	std::cout.precision(10);

	for (int i = 1; i <= N; ++i) {
		ld F; int T;
		std::cin >> F >> T;
		std::cout << "Case #" << i << ": " << f(F, T) << '\n';
		std::cout << "Case #" << i << ": " << f_p(F, T) << '\n';
	}
}