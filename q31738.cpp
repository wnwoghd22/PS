#include <iostream>

typedef long long ll;

ll N, M;

int main() {
	std::cin >> N >> M;
	if (N >= M) std::cout << 0;
	else {
		ll ret = 1;
		for (ll i = 2; i <= N; ++i) {
			ret = ret * i % M;
		}
		std::cout << ret;
	}
}