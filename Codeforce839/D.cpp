#include <iostream>
#include <cmath>

typedef long long int ll;
const int LEN = 200'001;
ll N, A[LEN];

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		ll max, min;
		ll asc = 0, desc = 0;
		std::cin >> N;
		std::cin >> A[0];
		max = min = A[0];
		for (int i = 1; i < N; ++i) {
			std::cin >> A[i];
			max = std::max(A[i], max);
			min = std::min(A[i], min);
			ll delta = A[i] - A[i - 1];
			if (delta > 0) asc++;
			if (delta < 0) desc++;
		}
		if (!desc) {
			std::cout << min << '\n';
			continue;
		}
		if (!asc) {
			std::cout << max << '\n';
			continue;
		}
		ll upper_bound = max, lower_bound = min;
		for (int i = 1; i < N; ++i) {
			ll delta = A[i] - A[i - 1];
			double bound = ((double)A[i] + A[i - 1]) / 2;
			// std::cout << bound << '\n';
			if (delta < 0) {
				lower_bound = std::max(lower_bound, (ll)ceil(bound));
				// std::cout << "lower: " << lower_bound << '\n';
			}
			if (delta > 0) {
				upper_bound = std::min(upper_bound, (ll)floor(bound));
				// std::cout << "upper: " << upper_bound << '\n';
			}
		}
		// std::cout << upper_bound << ' ' << lower_bound << '\n';
		if (upper_bound < lower_bound) std::cout << -1 << '\n';
		else std::cout << lower_bound << '\n';
	}
}