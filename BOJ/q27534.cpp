#include <iostream>

int T, N;
std::string S;

int main() {
	std::cin >> T;
	while (T--) {
		std::cin >> N >> S;
		if (N == 1 || N == 3) std::cout << -1 << '\n';
		else if (N == 2) {
			if (S == "10" || S == "01") std::cout << 0 << '\n';
			else std::cout << 1 << '\n';
		}
		else {
			int l = 0, r = N - 1;
			int cost = 2, flag = 1;
			for (l = 0; l < N / 2 - 1; ++l, --r) {
				if (S[l] == S[r]) {
					if (S[l + 1] == S[r - 1]) { flag = 0; break; }
					else { flag = 0; cost = 1; break; }
				}
				else {
					if (S[l + 1] == S[r - 1]) { flag = 0; cost = 1; break; }
					else if (S[l] != S[l + 1]) { flag = 0; cost = 0; break; }
				}
			}
			if (flag && ~N & 1) cost = 0;
			std::cout << cost << '\n';
		}
	}
}