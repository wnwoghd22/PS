#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

const int LEN = 4'587'520;
const int INF = 1e9;
int C, N, O, a, b, x, s;
std::string q;

struct Node { 
	int max, min, lazy;
	Node() : max(0), min(0), lazy(0) {}
	Node(int max, int min, int lazy) : max(max), min(min), lazy(lazy) {}
	Node operator+(const Node& r) const {
		return Node(std::max(max, r.max), std::min(min, r.min), 0);
	}
} seg_tree[LEN * 4];

void propagate(int s, int e, int i) {
	if (seg_tree[i].lazy) {
		seg_tree[i].max += seg_tree[i].lazy;
		seg_tree[i].min += seg_tree[i].lazy;

		seg_tree[i << 1].lazy += seg_tree[i].lazy;
		seg_tree[i << 1 | 1].lazy += seg_tree[i].lazy;

		seg_tree[i].lazy = 0;
	}
}

void update(int l, int r, int d, int s = 0, int e = C - 1, int i = 1) {
	propagate(s, e, i);

	if (e < l || r < s) return;
	if (l <= s && e <= r) {
		seg_tree[i].max += d;
		seg_tree[i].min += d;
		if (s ^ e) {
			seg_tree[i << 1].lazy += d;
			seg_tree[i << 1 | 1].lazy += d;
		}
		return;
	}
	int m = s + e >> 1;
	update(l, r, d, s, m, i << 1);
	update(l, r, d, m + 1, e, i << 1 | 1);
	seg_tree[i] = seg_tree[i << 1] + seg_tree[i << 1 | 1];
}

Node get(int l, int r, int s = 0, int e = C - 1, int i = 1) {
	propagate(s, e, i);

	if (e < l || r < s) return { 0, INF, 0 };
	if (l <= s && e <= r) return seg_tree[i];

	int m = s + e >> 1;
	return get(l, r, s, m, i << 1) + get(l, r, m + 1, e, i << 1 | 1);
}

int main() {
	freopen("input.txt", "r", stdin);

	std::cin >> C >> N >> O;
	while (O--) {
		std::cin >> q;
		if (q == "change") {
			std::cin >> x >> s;
			Node cur = get(x, x);
			if (s < 0) s = std::max(s, -cur.min);
			else if (s > 0) s = std::min(s, N - cur.max);
			update(x, x, s);
			std::cout << s << '\n';
		}
		else if (q == "groupchange") {
			std::cin >> a >> b >> s;
			Node cur = get(a, b);
			if (s < 0) s = std::max(s, -cur.min);
			else if (s > 0) s = std::min(s, N - cur.max);
			update(a, b, s);
			std::cout << s << '\n';
		}
		else if (q == "state") {
			std::cin >> x;
			std::cout << get(x, x).max << '\n';
		}
	}
}