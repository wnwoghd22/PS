#include <iostream>

typedef long long ll;

ll N, M, P[10], cnt[10];
int j = 1, head[50], tail[50];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> P[i];
		if (i && P[i] <= P[j]) j = i;
	}
	std::cin >> M;

	if (N == 1 || P[j] > M) return std::cout << (P[0] > M ? "0" : "1\n0\n0"), 0;

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

	ll D = cnt[j] + cnt[0];

	for (int k = 9; k > j; --k) {
		ll diff = (P[k] - P[j]);
		ll d = M / diff;
		if (d > cnt[j]) d = cnt[j];
		cnt[k] += d;
		cnt[j] -= d;
		M -= diff * d;
	}
	if (P[0] < P[j]) {
		for (int k = 9; k > 0; --k) {
			ll diff = (P[k] - P[0]);
			ll d = M / diff;
			if (d > cnt[0]) d = cnt[0];
			cnt[k] += d;
			cnt[0] -= d;
			M -= diff * d;
		}
	}

	for (int k = 9, i = 0; k >= 0 && i < 50; --k) {
		for (int d = 0; d < cnt[k] && i < 50; ++d)
			head[i++] = k;
	}

	for (int k = 0, i = 0; k < 10 && i < 50; ++k) {
		for (int d = 0; d < cnt[k] && i < 50; ++d)
			tail[i++] = k;
	}

	std::cout << D << '\n';
	for (int i = 0; i < std::min(D, 50ll); ++i) std::cout << head[i]; std::cout << '\n';
	for (int i = std::min(D, 50ll) - 1; i >= 0; --i) std::cout << tail[i]; std::cout << '\n';

}