#include <iostream>

const int MAX = 1'000'000;
int N, A, B, C, seg_tree[MAX * 4];

void update(int x, int d, int s = 1, int e = MAX, int i = 1) {
	if (x < s || e < x) return;
	seg_tree[i] += d;
	if (s == e) return;
	int m = s + e >> 1;
	update(x, d, s, m, i << 1);
	update(x, d, m + 1, e, i << 1 | 1);
}

int get_bound(int k, int s = 1, int e = MAX, int i = 1) {
	if (s == e) return s;
	int m = s + e >> 1;
	if (seg_tree[i << 1] >= k) return get_bound(k, s, m, i << 1);
	return get_bound(k - seg_tree[i << 1], m + 1, e, i << 1 | 1);
}

int main() {
	std::cin >> N;
	while (N--) {
		std::cin >> A;
		if (A - 1) std::cin >> B >> C, update(B, C);
		else {
			std::cin >> B;
			std::cout << (A = get_bound(B)) << '\n';
			update(A, -1);
		}
	}
}