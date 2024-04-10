#include <iostream>

const int LEN = 5001;

int N, K, t[LEN << 2];
int sp, ans[LEN];

void push(int x, int s = 1, int e = N, int i = 1) {
	if (x < s || e < x) return;
	if (s == e) { ++t[i]; return; }
	int m = s + e >> 1;
	push(x, s, m, i << 1); push(x, m + 1, e, i << 1 | 1);
	t[i] = t[i << 1] + t[i << 1 | 1];
}

int pop(int k, int s = 1, int e = N, int i = 1) {
	--t[i];
	if (s == e) return s;
	int m = s + e >> 1;
	if (t[i << 1] >= k) return pop(k, s, m, i << 1);
	else return pop(k - t[i << 1], m + 1, e, i << 1 | 1);
}

int main() {
	std::cin >> N >> K;
	for (int i = 1; i <= N; ++i) push(i);
	int k = K;
	while (1) {
		ans[sp++] = pop(k);
		if (!t[1]) break;
		k = (k + K - 1) % t[1];
		if (!k) k = t[1];
	}

	std::cout << "<";
	for (int i = 0; i < N; ++i) {
		std::cout << ans[i];
		if (i != N - 1) std::cout << ", ";
	}
	std::cout << ">";
}