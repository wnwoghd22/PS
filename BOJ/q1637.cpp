#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 2e4;
ll INF = 2'147'483'648;

int N, A[LEN], B[LEN], C[LEN];
ll f(int x) {
	ll cnt = 0;
	for (int i = 0; i < N; ++i) {
		if (x < A[i]) continue;
		cnt += (std::min(x, C[i]) - A[i]) / B[i] + 1;
	}
	return cnt;
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> A[i] >> C[i] >> B[i];
	ll l = 1, r = INF, m, ret = INF;
	while (l <= r) {
		m = l + r >> 1;
		if (f(m) & 1) {
			ret = std::min(ret, m);
			r = m - 1;
		}
		else l = m + 1;
	}
	if (ret == INF) std::cout << "NOTHING";
	else std::cout << ret << ' ' << f(ret) - f(ret - 1);
}