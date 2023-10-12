#include <iostream>

const int LEN = 5e5 + 2;

struct Node { int pre, nxt; } list[LEN];
int N, M, A[LEN], len, dp[LEN], idx[LEN], lis[LEN];

char c;

int lower_bound(int x) {
	int l = 0, r = len, m;
	while (l < r) {
		m = l + r >> 1;
		if (dp[m] < x) l = m + 1;
		else r = m;
	}
	return r;
}

int main() {
	std::cin >> N >> M;
	list[0].nxt = 1;
	for (int i = 1; i <= N; ++i) list[i] = { i - 1, i + 1 };
	for (int i = 0, x, y; i < M; ++i) {
		std::cin >> c >> x >> y; 
		int xl = list[x].pre;
		int xr = list[x].nxt;
		list[xl].nxt = xr;
		list[xr].pre = xl;
		if (c == 'A') {
			int yl = list[y].pre;
			list[x].pre = yl; list[yl].nxt = x;
			list[y].pre = x; list[x].nxt = y;
		}
		if (c == 'B') {
			int yr = list[y].nxt;
			list[x].nxt = yr; list[yr].pre = x;
			list[y].nxt = x; list[x].pre = y;
		}
	}
	int cur = list[0].nxt;
	for (int i = 0; i < N; ++i, cur = list[cur].nxt) A[i] = cur;
	// for (int i = 0; i < N; ++i) std::cout << A[i] << ' '; std::cout << std::endl;

	for (int i = 0; i < N; ++i) {
		int j = lower_bound(A[i]);
		if (j < len) {
			dp[j] = A[i];
			idx[i] = j;
		}
		else dp[idx[i] = len++] = A[i];
	}
	// for (int i = 0; i < len; ++i) std::cout << dp[i] << ' '; std::cout << std::endl;
	// for (int i = 0; i < N; ++i) std::cout << idx[i] << ' '; std::cout << std::endl;
	for (int i = N - 1, j = len - 1; i >= 0; --i)
		if (idx[i] == j)
			lis[j--] = A[i];

	// for (int i = 0; i < len; ++i) std::cout << lis[i] << ' ';

	std::cout << N - len << '\n';
	for (int i = 1, j = 0; i <= N; ++i) {
		if (lis[j] == i) ++j;
		else {
			if (i == 1) std::cout << "A " << 1 << ' ' << lis[j] << '\n';
			else std::cout << "B " << i << ' ' << i - 1 << '\n';
		}
	}
}