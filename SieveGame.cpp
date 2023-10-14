#include <iostream>

typedef long long ll;
const int LEN = 2e5 + 1;

int N;
ll t[LEN];
ll r;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> t[i];
	for (int i = 1; i <= N; ++i) {
		r += abs(t[i]);
		for (int j = i * 2; j <= N; j += i)
			t[j] -= t[i];
	}
	std::cout << r;
}