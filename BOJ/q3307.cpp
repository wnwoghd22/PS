#include <iostream>
#include <algorithm>

typedef long double ld;
const int LEN = 2e5 + 1;

int N, x[LEN], r[LEN];

int sp;
int s1[LEN];
ld s2[LEN];
ld ans[LEN];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> x[i] >> r[i];

		ld cur = r[i];
		int x2 = x[i];
		while (sp) {
			ld r1 = s2[sp - 1];
			int x1 = s1[sp - 1];
			ld d = x2 - x1;
			ld r2 = d * d / (4 * r1);
			cur = std::min(cur, r2);
			if (cur > r1) --sp;
			else break;
		}

		ans[i] = cur;
		s1[sp] = x2;
		s2[sp] = cur;
		++sp;
	}
	
	for (int i = 0; i < N; ++i)
		std::cout << ans[i] << '\n';
}