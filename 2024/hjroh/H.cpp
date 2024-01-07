#include <iostream>

const int LEN = 2e5 + 2;

int N, Q, A[LEN], fenwick[LEN];
int sum(int i) {
	int result = 0;
	while (i > 0) {
		result += fenwick[i];
		i -= i & -i;
	}
	return result;
}
void update(int i, int d) {
	while (i <= N) {
		fenwick[i] += d;
		i += i & -i;
	}
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> Q;
	for (int i = 1; i <= N; ++i) {
		std::cin >> A[i];
		if (A[i] != A[i - 1])
			update(i, 1);
	}
	for (int k = 0, q, i, x, l, r; k < Q; ++k) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> i >> x;
			if (A[i] == x) continue;
			
			if (A[i - 1] == x) update(i, -1);
			if (A[i - 1] == A[i]) update(i, 1);

			if (A[i + 1] == x) update(i + 1, -1);
			if (A[i + 1] == A[i]) update(i + 1, 1);

			A[i] = x;
		}
		if (q == 2) {
			std::cin >> l >> r;
			std::cout << sum(r) - sum(l) + 1 << '\n';
		}
	}
}