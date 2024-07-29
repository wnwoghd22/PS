#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

const int LEN = 1000;

int N;
std::string S;
std::string dict[LEN];

void solve() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> dict[i];
	}
	int x = 0;
	int cur = 0, k = N - 1;
	do cur = cur * 10 + S[x++] - '0'; while ((k /= 10));
	std::cout << dict[cur];
	dict[N++] = dict[cur];
	while (x < S.size()) {
		int nxt = 0, k = N - 1;
		do nxt = nxt * 10 + S[x++] - '0'; while ((k /= 10));
		dict[N - 1] += dict[nxt][0];
		dict[N++] = dict[nxt];
		std::cout << dict[cur = nxt];
	}
	std::cout << '\n';
}

int main() {
	freopen("input.txt", "r", stdin);

	std::cin.tie(0)->sync_with_stdio(0);
	for (int t = 1;; ++t) {
		std::cin >> S;
		if (S.size() == 1 && S[0] == '0') break;
		std::cout << "Case " << t << ": ";
		solve();
	}
}
