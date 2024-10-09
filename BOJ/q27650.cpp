#include <iostream>
#include <vector>

const int LEN = 5'000'001;
bool seive[LEN];
std::vector<int> prime;
int N;

int main() {
	std::cin >> N;
	for (int i = 2; i <= N; ++i) {
		if (seive[i]) continue;
		for (int j = i * 2; j <= N; j += i)
			seive[j] = true;
	}
	for (int i = 2; i <= N; ++i)
		if (!seive[i]) prime.push_back(i);
	
	// std::cout << prime.size();

	int l = 0, r = prime.size() - 1, m, q;
	int result = r;
	while (l <= r) {
		m = l + r >> 1;
		int p = prime[m];
		std::cout << "? " << p << std::endl;
		std::cin >> q;
		if (!q) {
			result = std::min(result, m);
			r = m - 1;
		}
		else l = m + 1;
	}
	std::cout << "! " << prime[result] << std::endl;
}