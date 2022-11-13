#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	int N, a, k, p = 0, h = -1, c = 0;
	std::vector<std::pair<int, int>> v;

	std::cin >> N;
	while (N--) {
		std::cin >> a >> k;
		v.push_back({ a, k });
	}
	std::sort(v.begin(), v.end());

	for (const std::pair<int, int>& e : v) {
		int interval = e.first - p;
		if (h < interval) ++c;
		p += interval; h = e.second;
	}
	std::cout << c;
}