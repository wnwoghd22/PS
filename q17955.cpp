#include <iostream>

const int LEN = 2e5 + 1;

int N, M, K;
int A[LEN + 2], fenwick[LEN], cnt[LEN];

int sum(int i) {
	int result = 0;
	while (i > 0) {
		result += fenwick[i];
		i -= i & -i;
	}
	return result;
}
void update(int i, int d) {
	while (i <= M) {
		fenwick[i] += d;
		i += i & -i;
	}
}
void update(int l, int r, int d) {
	update(l, d);
	update(r + 1, -d);
}

void query(int l, int r, int d) {
	if (l + 1 >= r - 1) return;
	update(l + 1, r - 1, d);
}

/// <summary>
/// Wrong code
/// Need to fix
/// </summary>
/// <returns></returns>
int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		std::cin >> A[i];
		++cnt[A[i]];
	}
	A[N + 1] = A[1];
	A[N + 2] = A[2];

	for (int i = 3, l, r; i <= N + 2; ++i) {
		if (A[i] == A[i - 1]) continue;
		if ((A[i - 2] < A[i - 1]) == (A[i] < A[i - 1])) {
			l = std::min(A[i - 2], A[i]);
			r = std::max(A[i - 2], A[i]);
			if (A[i] < A[i - 1]) {

			}
		}
		else {
			l = std::min(A[i - 1], A[i]);
			r = std::max(A[i - 1], A[i]);
		}
		std::cout << "l, r: " << l << ' ' << r << '\n';
		query(l, r, 1);
	}
	for (int i = 1; i <= M; ++i) {
		if (!cnt[i]) std::cout << -1 << ' ';
		else std::cout << N - cnt[i] + sum(i) << ' ';
	}
}