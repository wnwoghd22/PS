#include <iostream>
#include <cstring>

typedef long long int ll;
const int LEN = 3001;
ll N, K, M, dp1[LEN], dp2[LEN];
ll *p1, *p2, *temp;

int main() {
	int T;
	std::cin >> T;
	for (int t = 1; t <= T; ++t) {
		std::cin >> N >> K >> M;
		memset(dp1, 0, sizeof dp1);
		memset(dp2, 0, sizeof dp2);
		p1 = dp1;
		p2 = dp2;
		p1[0] = p2[0] = 1;
		for (ll i = 1; i <= N; ++i) {
			for (ll j = 1; j <= K; ++j) {
				p2[j] = ((i * p1[j - 1]) % M + p1[j]) % M;
			}
			temp = p1; p1 = p2; p2 = temp;
		}
		std::cout << '#' << t << ' ' << p1[K] << '\n';
	}
}