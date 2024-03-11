#include <iostream>
#include <algorithm>
#include <queue>

typedef long long ll;
const int LEN = 51;

int L, N, S[LEN];
struct E {
	int n;
	ll cnt;
	bool operator<(const E& r) const { return cnt == r.cnt ? n > r.n : cnt > r.cnt; }
};
std::priority_queue<E> pq;

int main() {
	std::cin >> L;
	for (int i = 1; i <= L; ++i) std::cin >> S[i];
	std::cin >> N;

	std::sort(S, S + L + 1);
	for (int i = 1; i <= L; ++i) {
		pq.push({ S[i], 0 });
		for (int s = S[i - 1] + 1, e = S[i] - 1, c = 0; c < N && s <= e; ++s, --e) {
			pq.push({ s, (ll)(s - S[i - 1]) * (S[i] - s) - 1 }); ++c;
			if (s == e) break;
			pq.push({ e, (ll)(e - S[i - 1]) * (S[i] - e) - 1 }); ++c;
		}
	}

	while (pq.size() && N--) {
		std::cout << pq.top().n << ' ';
		pq.pop();
	}
	if (N) {
		for (int i = 1; i <= N; ++i) std::cout << S[L] + i << ' ';
	}
}