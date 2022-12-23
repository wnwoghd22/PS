#include <iostream>

const int LEN = 1'000'001;
int N, K, Z[LEN];

void z(std::string s) {
	int l = 0, r = 0, len = s.length(), k;
	for (int i = 1; i < len; ++i) {
		if (i > r) {
			l = r = i;
			while (r < len && s[r - l] == s[r]) ++r;
			Z[i] = r - l, --r;
		}
		else {
			k = i - l;
			if (Z[k] < r - i + 1) Z[i] = Z[k];
			else {
				l = i;
				while (r < len && s[r - l] == s[r]) ++r;
				Z[i] = r - l, --r;
			}
		}
	}
}

int main() {
	std::string S;
	std::cin >> N >> K >> S;
	z(S);
	if (K >= N) {
		std::cout << N;
	}
	else {
		int max = 0;
		for (int i = 1; i < N; ++i) {
			if (i + Z[i] == N) {
				int t = (N + K) / i;
				if (t >= 2 && t * i >= N) max = std::max(max, i);
			}
		}
		std::cout << max;
	}
}
