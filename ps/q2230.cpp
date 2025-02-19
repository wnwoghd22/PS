#include <iostream>
#include <algorithm>

const int LEN = 1e5;

int N, M, A[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	std::sort(A, A + N);
	int ret = 2e9;
	for (int l = 0, r = 0; r < N; ++l) {
		while (r < N && A[r] - A[l] < M) ++r;
		if (A[r] - A[l] >= M)
			ret = std::min(ret, A[r] - A[l]);
	}
	std::cout << ret;
}