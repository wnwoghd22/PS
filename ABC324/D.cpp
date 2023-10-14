#include <iostream>
#include <cstring>
#include <string>

typedef long long ll;
int N, cnt[10], cur[10];
std::string S;

int main() {
	std::cin >> N >> S;
	for (int i = 0; i < N; ++i) cnt[S[i] - '0']++;
	int ret = 0;

	for (ll i = 0, j, k; ; ++i) {
		j = i * i;
		k = 0;
		memset(cur, 0, sizeof cur);
		for (int l = 0; l < N; ++l) {
			cur[j % 10]++;
			j /= 10;
		}
		if (j) break;
		for (int l = 0; l < 10; ++l) {
			if (cnt[l] ^ cur[l]) {
				k++;
				break;
			}
		}
		if (!k) {
			// std::cout << i * i << '\n';
			++ret;
		}
	}
	std::cout << ret;
}