#include <iostream>
#include <vector>

const int LEN = 100'001;

char S[LEN];
int N, K, O[LEN];

struct Seg {
	int s, e;
};
std::vector<Seg> segs;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> K >> S;
	char pre = '$';
	for (int i = 0, s = 0, e = 0; i < N; ++i) {
		// std::cout << pre << ' ' << S[i] << ' ' << s << ' ' << e << '\n';
		if (i == N - 1 && S[i] == pre) e = i;
		if (S[i] != pre || i == N - 1) {
			int cnt = e - s + 1;
			if (cnt >= 2 * K) { // impossible to split
				std::cout << K - 1;
				return 0;
			}
			if (cnt >= K) {
				segs.push_back({ s, e });
				for (int j = s; j <= e; ++j) O[j] = segs.size();
			}
			s = e = i;
		}

		if (S[i] == pre) e = i;
		pre = S[i];
	}

	// for (int i = 0; i < N; ++i) std::cout << O[i] << ' '; std::cout << '\n';

	int ret = K - 1;
	for (int l = N; l >= K; --l) {
		int cnt = segs.size();
		for (int i = l - 1; i < N; i += l) {
			if (!O[i]) continue;
			int s = segs[O[i] - 1].s;
			int e = segs[O[i] - 1].e;

			if (i - s + 1 < K && e - i < K) cnt--;
			else break;
		}
		if (!cnt) {
			ret = l;
			break;
		}
	}
	std::cout << ret;
}