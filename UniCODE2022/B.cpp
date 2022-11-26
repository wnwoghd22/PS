#include <iostream>
#include <algorithm>

typedef long long int ll;
const ll LEN = 300'000;
ll N, D, H[LEN];

int main() {
	std::cin >> N >> D;
	for (int i = 0; i < N; ++i) std::cin >> H[i];
	ll h = std::max(*std::max_element(H, H + N) - D, 0ll);
	
	ll result = 0;
	for (int i = 0; i < N; ++i) result += std::max(H[i] - h, 0ll);
	std::cout << result;
}