#include <iostream>

typedef long long ll;
const int LEN = 250'001;
int N, l, r;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	l = N, r = 0;
	ll C, z = 0, r = 0, l = -1, c = 0;
	for (int i = 0; i < N; ++i) {
		std::cin >> C;
		z += C;
		if (C) {
			if (!~l) l = r;
			else c += (r + 1) / 2; 
			r = 0;
		}
		else r++;
	}
	if (!z) {
		std::cout << N / 2;
		return 0;
	}
	c += (l + r + 1) / 2;
	std::cout << z + c;
}