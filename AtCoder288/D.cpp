#include <iostream>

typedef long long int ll;
ll arr[200'050], d[200'050];
int N, K, Q, L, R;

int main() {
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		std::cin >> arr[K + i];
		d[K + i] = arr[K + i];
	}
	for (int i = 0; i < N; ++i) {
		ll c = d[K + i];
		d[K + i] = -c;
		for (int j = 1; j < K; ++j) {
			d[K + i + j] -= c;
		}
		for (int k = 0; k < N + K; ++k)
			std::cout << d[k] << ' ';
		std::cout << '\n';
	}
	for (int i = 0; i < N + K; ++i)
		std::cout << d[i] << ' ';
	std::cout << '\n';

	std::cin >> Q;
	while (Q--) {
		std::cin >> L >> R;
		L += K - 2; R += K - 1;
		std::cout << L << ' ' << R << '\n';
		bool flag = true;
		for (int i = 0; i < K - 1; ++i) {
			std::cout << d[L - i] << ' ' << d[R - i] << '\n';
			if (d[L - i] != d[R - i]) {
				flag = false;
				break;
			}
		}
		if (flag) std::cout << "Yes\n";
		else std::cout << "No\n";
	}
}
