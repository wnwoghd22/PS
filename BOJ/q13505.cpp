#include <iostream>

const int LEN = 100'001;
int N, ret = 0, sz = 1, t[LEN * 20][2];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	ret = 0;
	for (int i = 0, a, x; i < N; ++i) {
		std::cin >> a;
		x = 0;
		for (int k = 1, l, d = 30, b; k && d >= 0; --d, k = l) {
			if (l = t[k][b = ~a >> d & 1]) x += 1 << d;
			else l = t[k][!b];
		}
		if (x > ret) ret = x;
		for (int k = 1, d = 30, b; d >= 0; k = t[k][a >> d-- & 1])
			if (!t[k][b = a >> d & 1]) t[k][b] = ++sz;
	}
	std::cout << ret;
}