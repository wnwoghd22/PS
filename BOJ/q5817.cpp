#include <iostream>

const int LEN = 200'001;
const int INF = 1e9;

int N, M, idx[LEN], ord[LEN];
struct Node {
	int min, max;
	Node operator^(const Node& r) const {
		return { std::min(min, r.min), std::max(max, r.max) };
	}
} t[LEN << 2];
void update(int x, int d, int s = 1, int e = N, int i = 1) {
	if (x < s || e < x) return;
	if (s == e) { t[i].min = t[i].max = d; return; }
	int m = s + e >> 1;
	update(x, d, s, m, i << 1); update(x, d, m + 1, e, i << 1 | 1);
	t[i] = t[i << 1] ^ t[i << 1 | 1];
}

Node get(int l, int r, int s = 1, int e = N, int i = 1) {
	if (r < s || e < l) return { INF, -INF };
	if (l <= s && e <= r) return t[i];
	int m = s + e >> 1;
	return get(l, r, s, m, i << 1) ^ get(l, r, m + 1, e, i << 1 | 1);
}

int main() {
	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		std::cin >> idx[i];
		update(idx[i], i);
	}
	for (int i = 0, q, x, y, a, b; i < M; ++i) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> x >> y;
			a = idx[x], b = idx[y];
			update(b, x);
			update(a, y);
			std::swap(idx[x], idx[y]);
		}
		if (q == 2) {
			std::cin >> a >> b;
			Node range = get(a, b);
			if (b - a == range.max - range.min) std::cout << "YES\n";
			else std::cout << "NO\n";
		}
	}
}
