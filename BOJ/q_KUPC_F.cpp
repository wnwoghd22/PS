#include <iostream>

const int LEN = 40001;

int N, M, R, S;
int H[LEN];
int W[LEN];
int A[2000];

int main() {
	std::cin >> N >> M >> R;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	for (int i = 0, B; i < M; ++i) std::cin >> B, H[B] = 1;
	for (int i = 0; i < N; ++i)
		for (int j = i + 1; j < N; ++j)
			W[abs(A[i] - A[j])] = 1;
	S = -1;
	for (int l = 0, r = LEN - 1; l < LEN; ++l) {
		if (W[l]) {
			while (r > 0 && (!H[r] || l * r > R * 2)) --r;
			if (l * r && l * r > S) S = l * r;
		}
	}
	if (~S) std::cout << (S / 2) << '.' << (5 * (S & 1));
	else std::cout << -1;
}