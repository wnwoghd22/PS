#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

int A[1000], N;
int get_tier(char c) {
	if (c == 'B') return 0;
	if (c == 'S') return 1;
	if (c == 'G') return 2;
	if (c == 'P') return 3;
	if (c == 'D') return 4;
}
char get_tier(int i) {
	if (i == 0) return 'B';
	if (i == 1) return 'S';
	if (i == 2) return 'G';
	if (i == 3) return 'P';
	if (i == 4) return 'D';
}

int main() {
	char c; int n;
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		scanf(" %c%d", &c, &n);
		A[i] = get_tier(c) * 10000 + (2000 - n);
	}
	std::vector<int> v;
	for (int i = 0; i < N - 1; ++i) {
		if (A[i] > A[i + 1])
			v.push_back(A[i]), v.push_back(A[i + 1]);
	}
	if (v.empty()) std::cout << "OK";
	else {
		std::sort(v.begin(), v.end());
		std::cout << "KO\n";
		int min = v[0];
		int max = v.back();
		std::cout << min << ' ' << max << '\n';
		std::cout << get_tier(min / 10000) << min % 10000 << ' ';
		std::cout << get_tier(max / 10000) << max % 10000;
	}
}