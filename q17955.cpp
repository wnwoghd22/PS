#include <iostream>
#include <vector>

const int LEN = 2e5 + 1;
int abs(int i) { return i > 0 ? i : -i; }

int N, M;
std::vector<int> pos[LEN];

struct Node {
	int l, m, r;
	bool f;
	Node operator+(const Node& o) const {
		Node ret = { l, m + o.m, o.r, 0 };
		if (r && o.l && (r > 0) != (o.l > 0)) { // merge middle
			ret.f = f && o.f;
			if (!f && !o.f) ret.m += abs(r) + abs(o.l) >> 1;
			if (f) ret.l += l > 0 ? abs(o.l) : -abs(o.l);
			if (o.f) ret.r += o.r > 0 ? abs(r) : -abs(r);
		}
		else {
			if (!f) ret.m += abs(r) >> 1;
			if (!o.f) ret.m += abs(o.l) >> 1;
		}
		return ret;
	}
} t[LEN << 3];

void init(int s = 1, int e = N * 2, int i = 1) {
	t[i] = { 1, 0, 1, s == e };
	if (s == e) return;
	int m = s + e >> 1;
	init(s, m, i << 1); init(m + 1, e, i << 1 | 1);
}

void update(int x, int d, int s = 1, int e = N * 2, int i = 1) {
	if (x < s || e < x) return;
	if (s == e) {
		t[i] = { d, 0, d, !!d };
		return;
	}
	int m = s + e >> 1;
	update(x, d, s, m, i << 1); update(x, d, m + 1, e, i << 1 | 1);
	t[i] = t[i << 1] + t[i << 1 | 1];
}
Node query(int l, int r, int s = 1, int e = N * 2, int i = 1) {
	if (r < s || e < l) return { 0, 0, 0, 0 };
	if (l <= s && e <= r) return t[i];
	int m = s + e >> 1;
	return query(l, r, s, m, i << 1) + query(l, r, m + 1, e, i << 1 | 1);
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	for (int i = 1, a; i <= N; ++i) {
		std::cin >> a;
		pos[a].push_back(i);
	}
	init();
	for (int i = 1; i <= M; ++i) {
		if (pos[i].empty()) {
			std::cout << -1 << ' ';
			continue;
		}
		for (const int& x : pos[i])
			update(x, 0), update(x + N, 0);
		
		std::cout << N - pos[i].size() + query(pos[i][0], pos[i][0] + N).m << ' ';

		for (const int& x : pos[i])
			update(x, -1), update(x + N, -1);
	}
}