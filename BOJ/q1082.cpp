#include <iostream>

int N, M, P[10];
int j = 1, cnt[10];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> P[i];
		if (i && P[i] <= P[j]) j = i;
	}
	std::cin >> M;

	if (N == 1 || P[j] > M) return std::cout << (P[0] > M ? -1 : 0), 0;
	
	// std::cout << "min: " << j << '\n';

	if (P[0] < P[j]) {
		cnt[j]++;
		M -= P[j];
		cnt[0] += M / P[0];
		M -= P[0] * cnt[0];
	}
	else {
		cnt[j] += M / P[j];
		M -= P[j] * cnt[j];
	}

	// for (int k = 0; k < 10; ++k) std::cout << cnt[k] << ' '; std::cout << '\n';

	for (int k = 9; k > j; --k) {
		int diff = (P[k] - P[j]);
		int d = M / diff;
		if (d > cnt[j]) d = cnt[j];
		cnt[k] += d;
		cnt[j] -= d;
		M -= diff * d;
	}
	if (P[0] < P[j]) {
		for (int k = 9; k > 0; --k) {
			int diff = (P[k] - P[0]);
			int d = M / diff;
			if (d > cnt[0]) d = cnt[0];
			cnt[k] += d;
			cnt[0] -= d;
			M -= diff * d;
		}
	}

	// for (int k = 0; k < 10; ++k) std::cout << cnt[k] << ' '; std::cout << '\n';

	for (int k = 9; k >= 0; --k) {
		for (int d = 0; d < cnt[k]; ++d)
			std::cout << k;
	}
}