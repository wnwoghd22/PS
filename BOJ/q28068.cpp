#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 1e5;

struct Book { int a, b; } A[LEN], B[LEN];
int N, M, K;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0, a, b; i < N; ++i) {
		std::cin >> a >> b;
		if (a <= b) A[M++] = { a, b };
		if (a > b) B[K++] = { a, b };
	}
	std::sort(A, A + M, [](const Book& l, const Book& r) -> bool { return l.a < r.a; });
	std::sort(B, B + K, [](const Book& l, const Book& r) -> bool { return l.b > r.b; });
	ll C = 0;
	bool ret = 1;
	for (int i = 0; i < M; ++i) {
		if (C < A[i].a) {
			ret &= 0;
			break;
		}
		C += A[i].b - A[i].a;
	}
	for (int i = 0; i < K; ++i) {
		if (C < B[i].a) {
			ret &= 0;
			break;
		}
		C += B[i].b - B[i].a;
	}
	std::cout << ret;
}
