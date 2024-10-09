#include <iostream>
#include <algorithm>

const int LEN = 1'000'000;
std::pair<int, int> A[LEN];
int N, M;

int main() {
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		std::cin >> A[i].first;
		A[i].second = i + 1;
	}
	std::sort(A, A + N);

	for (int i = N - 1; i >= std::max(N - 4, 1); --i) {
		if (A[i].first - A[i - 1].first > M) {
			std::cout << "NO";
			return 0;
		}
	}
	std::cout << "YES\n";
	for (int i = N - 1; i >= std::max(N - 2, 0); --i) {
		std::cout << A[i].second << ' ';
	}
	for (int i = 0; i < N - 2; ++i) {
		std::cout << A[i].second << ' ';
	}
}