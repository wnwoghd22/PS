#include <iostream>

const int LEN = 2e5 + 1;
char l, S[LEN];
int N, f, odd, min, d;

int main() {
	std::cin >> N >> S;
	for (int i = 0; i < N; ++i) {
		if (S[i] == 'F') ++f;
		else {
			if (!l) { // leftmost segment
				if (f) {
					odd = 1;
					d += f;
				}
			}
			else {
				if (l ^ S[i]) {
					min += f & 1;
					d += f & ~1;
				}
				else {
					min += ~f & 1;
					d += f + 1 & ~1;
				}
			}
			f = 0;
			l = S[i];
		}
	}
	if (f) {
		d += f - (f == N);
		odd = 1;
	}
	std::cout << (d >> !odd) + 1 << '\n';
	for (int i = 0; i <= d; i += 1 + !odd) 
		std::cout << min + i << '\n';
}