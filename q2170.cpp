#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::pair<int, int>> v;

int main() {
	int N, x, y, len = 0;
	std::cin >> N;
	while (N--) {
		int x, y;
		std::cin >> x >> y;
		v.push_back({ x, y });
	}
	std::sort(v.begin(), v.end());
	x = v[0].first, y = v[0].second;
	len += y - x;

	for (const auto& pii : v) {
		std::cout << pii.first << ' ' << pii.second << '\n';
		if (pii.first < y) {
			if (pii.second > y) {
				len += pii.second - y;
				y = pii.second;
			}
		}
		else {
			len += pii.second - pii.first;
			x = pii.first, y = pii.second;
		}
	}
	std::cout << len;
}