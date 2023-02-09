#include <iostream>

void solve() {
	int N, A, B, Sa, Sb, eff;
	std::cin >> N;
	eff = 1;
	Sa = Sb = A = B = 0;
	while (N) {
		int d = N % 10;
		N /= 10;
		int half = d / 2;
		if (Sa < Sb) {
			Sb += half, Sa += d - half;
			A += eff * (d - half), B += eff * half;
		}
		else {
			Sa += half, Sb += d - half;
			B += eff * (d - half), A += eff * half;
		}
		eff *= 10;
	}
	std::cout << A << ' ' << B << '\n';
}

int main() {
	int T;
	std::cin >> T;
	while (T--) solve();
}