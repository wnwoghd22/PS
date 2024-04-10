#include <iostream>
#include <cstring>

typedef long long int ll;
const int LEN = 200002;
ll a[LEN], s0[LEN], s1[LEN];

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		memset(s0, 0, sizeof s0);
		memset(s1, 0, sizeof s1);

		ll N, count = 0;
		std::cin >> N;
		for (int i = 1; i <= N; ++i) {
			std::cin >> a[i];
			if (!a[i]) {
				count += s1[i - 1];
				s0[i] = s0[i - 1] + 1;
				s1[i] = s1[i - 1];
			}
			else {
				s1[i] = s1[i - 1] + 1;
				s0[i] = s0[i - 1];
			}
		}
		ll result = count;
		for (int i = 1; i <= N; ++i) {
			int c1 = s1[i - 1], c0 = s0[N] - s0[i];
			if (!a[i]) {
				result = std::max(result, count - c1 + c0);
			}
			else {
				result = std::max(result, count + c1 - c0);
			}
		}
		std::cout << result << '\n';
	}
}