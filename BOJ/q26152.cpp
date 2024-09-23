#include <iostream>

int N, Q, w;
const int LEN = 250'000;
int A[LEN + 2], B[LEN + 2], M[LEN + 2];

int get_score(int size) { // binary search
	int l = 0, r = LEN + 1, mid, result = 0;
	while (l <= r) {
		mid = (l + r) / 2;
		if (M[mid] >= size) {
			result = std::max(result, mid);
			l = mid + 1;
		}
		else r = mid - 1;
	}
	return result;
}

int main() {
	M[0] = 2e9;
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	for (int i = 1; i <= N; ++i) std::cin >> B[i];
	for (int i = 1; i <= N; ++i) M[i] = std::min(A[i] - B[i], M[i - 1]);

	std::cin >> Q;
	while (Q--) {
		std::cin >> w;
		std::cout << get_score(w) << '\n';
	}
}