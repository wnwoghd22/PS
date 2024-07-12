#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

int N;
int get_middle(int s) {
	int cnt = 0, x = s;
	while (x) {
		cnt++;
		x -= x & -x;
	}
	// std::cout << "cnt: " << cnt << '\n';
	if (cnt == 0) return 0;
	int mid = cnt / 2;
	int cur = 0;
	for (int i = 0; i < 31; ++i) {
		if (s & 1 << i) cur++;
		// std::cout << i << '\n';
		if (cur == mid + 1) return i;
	}
}

void print_set(int s) {
	std::cout << "<";
	for (int i = 0; i < N; ++i) std::cout << (i + 1) * !!(s & 1 << i) << ',';
	std::cout << "> ";
}

int main() {
	std::cin >> N;
	std::string S = std::to_string(N) + ".out";
	// std::string S = std::to_string(N) + "_naive.out";
	freopen(S.c_str(), "r", stdin);
	std::string SS = std::to_string(N) + ".ret.out";
	// std::string SS = std::to_string(N) + "_naive.ret.out";
	freopen(SS.c_str(), "w", stdout);
	int cnt;
	std::cin >> cnt;
	int s[3] = { (1 << N) - 1, 0, 0 };

	std::cout << 0 << ' ';
	for (int i = 0; i < 3; ++i) {
		print_set(s[i]);
	}
	std::cout << '\n';

	for (int i = 0, u, v; i < cnt; ++i) {
		std::cin >> u >> v;
		int m = get_middle(s[u - 1]);
		s[u - 1] &= ~(1 << m);
		s[v - 1] |= 1 << m;

		std::cout << i + 1 << " (" << u << ' ' << v << ") ";
		for (int j = 0; j < 3; ++j) {
			print_set(s[j]);
		}
		std::cout << '\n';
	}
}