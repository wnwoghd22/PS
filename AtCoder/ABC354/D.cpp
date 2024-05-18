#include <iostream>

typedef long long ll;
const int INF = 1e9;

int main() {
	ll A, B, C, D;
	std::cin >> A >> B >> C >> D;
	ll H = D - B;
	ll ret = 0;

	A += INF;
	B += INF;
	C += INF;
	D += INF;

	ll even, odd;
	if (B & 1) {
		odd = (H + 1) / 2;
		even = H - odd;
	}
	else {
		even = (H + 1) / 2;
		odd = H - even;
	}

	// std::cout << H << '\n';
	// std::cout << even << ' ' << odd << '\n';

	while (A < C && (C - A) % 4) {
		switch (A % 4) {
		case 0:
			ret += even * 2 + odd;
			break;
		case 1:
			ret += even + odd * 2;
			break;
		case 2:
			ret += odd;
			break;
		case 3:
			ret += even;
			break;
		}
		++A;
	}
	ll W = C - A;

	ret += H * W;

	std::cout << ret;
}