#include <iostream>

typedef long long ll;
const int LEN = 1e6 + 1;
int N, B, C;
ll S, A[LEN], _B[LEN], _C[LEN];

int main() {
	ll result = 0;
	std::cin >> N >> B >> C;
	
	for (int i = 1; i <= N; ++i) std::cin >> A[i], S += A[i];
	if (C >= B) {
		std::cout << B * S;
		return 0;
	}

	for (ll b, c, i = 1; i <= N; ++i) {
		b = std::min(_B[i - 1], A[i]);
		result += b * C; A[i] -= b; _C[i] += b;

		c = std::min(_C[i - 1], A[i]);
		result += c * C; A[i] -= c;

		_B[i] += A[i]; result += _B[i] * B;
	}
	std::cout << result;
}