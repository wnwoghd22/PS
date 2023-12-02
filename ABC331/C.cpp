#include <iostream>

typedef long long ll;

const int LEN = 2e5 + 1;
const int MAX = 1e6 + 1;

int N, A[LEN];
ll sum[MAX];

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		std::cin >> A[i];
		sum[A[i]] += A[i];
	}
	for (int i = 1; i < MAX; ++i) sum[i] += sum[i - 1];
	for (int i = 1; i <= N; ++i) std::cout << sum[MAX - 1] - sum[A[i]] << ' ';
}