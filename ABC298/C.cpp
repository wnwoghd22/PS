#include <iostream>
#include <map>

const int LEN = 2e5 + 1;
std::map<int, int> buckets[LEN];
std::map<int, int> cards[LEN];
int N, Q;

int main() {
	std::cin >> N >> Q;
	for (int k = 0, q, i, j; k < Q; ++k) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> i >> j;
			cards[i][j] = 1;
			if (buckets[j].find(i) == buckets[j].end()) buckets[j][i] = 0;
			buckets[j][i]++;
		}
		if (q == 2) {
			std::cin >> i;
			for (const auto [k, v] : buckets[i])
				for (int i = 0; i < v; ++i) std::cout << k << ' ';
			std::cout << '\n';
		}
		if (q == 3) {
			std::cin >> i;
			for (const auto [k, v] : cards[i]) std::cout << k << ' ';
			std::cout << '\n';
		}
	}
}