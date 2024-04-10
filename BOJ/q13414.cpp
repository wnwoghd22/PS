#include <iostream>
#include <algorithm>
#include <map>

const int LEN = 5e5;

struct E {
	std::string i;
	int o;
	bool operator<(const E& r) const { return o < r.o; }
} e[LEN];

std::map<std::string, int> map;

int N, K, L;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> K >> L;
	for (int i = 0; i < L; ++i) {
		std::string j;
		std::cin >> j;
		map[j] = i;
	}
	for (const auto& el : map)
		e[N++] = { el.first, el.second };
	std::sort(e, e + N);
	for (int i = 0; i < std::min(K, N); ++i) {
		printf("%08d\n", e[i].i);
	}
}