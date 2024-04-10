#include <iostream>
#include <algorithm>

const int LEN = 1'000'001;
int M, I, Z[LEN];

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
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::string S;
	std::cin >> S;
	std::reverse(S.begin(), S.end());
	z(S);
	Z[0] = S.length();
	std::reverse(Z, Z + S.length());
	std::cin >> M;
	while (M--) {
		std::cin >> I;
		std::cout << Z[I - 1] << '\n';
	}
}
