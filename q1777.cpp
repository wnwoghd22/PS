#include <iostream>

const int LEN = 100'001;

int N, A[LEN], B[LEN], t[LEN];
int sum(int i) {
	int result = 0;
	while (i > 0) {
		result += t[i];
		i -= i & -i;
	}
	return result;
}
void update(int i, int d) {
	while (i <= N) {
		t[i] += d;
		i += i & -i;
	}
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	for (int i = N, l, r ,m, j; i >= 1; --i) {
		l = 1, r = N, j = 1;
		while (l <= r) {
			m = l + r >> 1;
			if (i - m + sum(m - 1) >= A[i]) {
				j = std::max(j, m);
				l = m + 1;
			}
			else r = m - 1;
		}
		B[j] = i;
		update(j, 1);
	}
	for (int i = 1; i <= N; ++i) std::cout << B[i] << ' ';
}