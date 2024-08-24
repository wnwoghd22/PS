#include <iostream>

typedef long long ll;
const int LEN = 2e5;

int N, H[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> H[i];
	
	ll t = 0;
	for (int i = 0; i < N; ++i) {
		while (t % 3 && H[i] > 0) {
			t++;
			H[i] -= t % 3 ? 1 : 3;
		}
		if (H[i] <= 0) continue;
		ll x = H[i] / 5;
		t += x * 3;
		H[i] %= 5;
		if (H[i] >= 3) t += 3;
		else t += H[i];
	}
	std::cout << t;
}