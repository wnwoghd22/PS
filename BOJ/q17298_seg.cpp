#include <iostream>

const int LEN = 1'000'002;

int N, A[LEN];

int seg_max[LEN << 2];
void update(int x, int d, int s = 1, int e = N, int i = 1) {
	if (x < s || e < x) return;
	if (s == e) { seg_max[i] = d; return; }
	int m = s + e >> 1;
	update(x, d, s, m, i << 1);
	update(x, d, m + 1, e, i << 1 | 1);
	seg_max[i] = std::max(seg_max[i << 1], seg_max[i << 1 | 1]);
}
int nge(int x, int s = 1, int e = N, int i = 1) {
	if (e <= x || seg_max[i] <= A[x]) return N + 1;
	if (s == e) return s;
	int m = s + e >> 1;
	int l = nge(x, s, m, i << 1);
	if (l <= N) return l;
	return nge(x, m + 1, e, i << 1 | 1);
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		std::cin >> A[i];
		update(i, A[i]);
	}
	A[N + 1] = -1;
	for (int i = 1; i <= N; ++i) {
		int j = nge(i);
		std::cout << A[j] << ' ';
	}
}