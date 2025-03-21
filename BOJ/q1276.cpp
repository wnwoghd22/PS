#include <iostream>
#include <algorithm>

struct E {
	int y, x1, x2;
	bool operator<(const E& o) const {
		return y < o.y;
	}
} e[100];

int N, h[10001];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i)
		std::cin >> e[i].y >> e[i].x1 >> e[i].x2;
	std::sort(e, e + N);
	int ret = 0;
	for (int i = 0; i < N; ++i) {
		ret += e[i].y * 2 - h[e[i].x1] - h[e[i].x2 - 1];
		for (int j = e[i].x1; j < e[i].x2; ++j)
			h[j] = e[i].y;
	}
	std::cout << ret;
}