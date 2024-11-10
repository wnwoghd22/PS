#include <iostream>

typedef long long ll;
ll N, A, Q, R, S;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (ll k = 1; k <= N; ++k) {
		std::cin >> A;
		S += A;
		Q += 2 * S - A;
		R += Q;
		std::cout << R << ' ';
	}
}