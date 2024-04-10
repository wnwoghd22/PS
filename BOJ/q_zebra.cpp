#include <iostream>

int N, M, L, K;
char S[1001];
int f() {
	bool b = 0;
	int ret = 0;
	for (int i = 0; S[i]; ++i) {
		if (S[i] == '1') {
			if (!b) ++ret;
			b = 1;
		}
		else b = 0;
	}
	return ret;
}

int main() {
	std::cin >> N >> L;
	while (N--) {
		std::cin >> S;
		L = f();
		if (L > K) {
			M = 1;
			K = L;
		}
		else if (L == K) ++M;
	}
	std::cout << K << ' ' << M;
}