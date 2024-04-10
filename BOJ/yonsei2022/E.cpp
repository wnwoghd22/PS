#include <iostream>

typedef long long int ll;

bool A[1'000'001];

int main() {
	ll N, cost = 0;
	std::cin >> N;

	for (int i = 2; i <= N; ++i) {
		for (int j = i; j <= N; j += i) {
			if (A[j]) continue;
			A[j] = true;
			cost += i;
		}
	}
	std::cout << cost;
}