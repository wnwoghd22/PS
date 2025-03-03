#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 2e5;
int N, A[LEN];
ll S;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> A[i];
		S += A[i];
	}
	std::sort(A, A + N);
	ll l1 = A[0], l2 = A[1];
	ll r1 = A[N - 2], r2 = A[N - 1];
	ll l = 2 * l1 * l2 - l1 - l2;
	ll r = 2 * r1 * r2 - r1 - r2;
	std::cout << S + std::max({ 0ll, l, r });
}