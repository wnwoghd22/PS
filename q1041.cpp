#include <iostream>
#include <algorithm>

typedef long long int ll;
ll N, A[6], S1, S2, S3;

int main() {
	std::cin >> N; for (int i = 0; i < 6; ++i) std::cin >> A[i];
	if (N == 1) {
		ll sum = 0;
		for (int i = 0; i < 6; ++i) sum += A[i];
		std::cout << sum - *std::max_element(A, A + 6);
		return 0;
	}
	S1 = *std::min_element(A, A + 6);
	S2 = std::min({
		A[0] + A[1], A[0] + A[2], A[0] + A[3], A[0] + A[4],
		A[5] + A[1], A[5] + A[2], A[5] + A[3], A[5] + A[4],
		A[1] + A[2], A[1] + A[3], A[4] + A[3], A[4] + A[2]
		});
	S3 = std::min({
		A[0] + A[1] + A[2], A[0] + A[1] + A[3], A[0] + A[4] + A[2], A[0] + A[4] + A[3],
		A[5] + A[1] + A[2], A[5] + A[1] + A[3], A[5] + A[4] + A[2], A[5] + A[4] + A[3],
		});
	std::cout << 4 * S3 + (8 * N - 12) * S2 + (5 * N * N - 16 * N + 12) * S1;
}