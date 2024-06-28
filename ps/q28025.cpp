#include <iostream>

typedef long long ll;
const int LEN = 2e5 + 1;
const char BESSIE[] = "bessie";

int N, U, P;
char C, S[LEN];

struct Node {
	ll nxt[6];
	ll pre[6];
	ll suf[6];
	ll ret;
	Node() : nxt(), pre(), suf(), ret(0) {}
	Node operator+(const Node& o) const {
		Node n;
		n.ret = ret + o.ret;
		for (int i = 0; i < 6; ++i) {
			n.nxt[i] = o.nxt[nxt[i]];
			n.pre[i] += o.pre[i];
			n.pre[o.nxt[i]] += pre[i];
			n.suf[i] = suf[i] + o.suf[nxt[i]];
			n.ret += pre[i] * o.suf[i];
		}
		return n;
	}
} t[LEN << 2];

Node get(char c, int p) {
	Node n;
	for (int i = 0; i < 6; ++i) {
		if (c == BESSIE[i]) n.nxt[i] = (i + 1) % 6;
		else n.nxt[i] = i;
	}
	n.pre[n.nxt[0]] = 1;
	if (n.nxt[5] == 0) n.suf[5] = N - p;
	return n;
}

void init(int s = 0, int e = N - 1, int i = 1) {
	if (s == e) { t[i] = get(S[s], s); return; }
	int m = s + e >> 1;
	init(s, m, i << 1); init(m + 1, e, i << 1 | 1);
	t[i] = t[i << 1] + t[i << 1 | 1];
}

void update(int p, char c, int s = 0, int e = N - 1, int i = 1) {
	if (p < s || e < p) return;
	if (s == e) { t[i] = get(c, p); return; }
	int m = s + e >> 1;
	update(p, c, s, m, i << 1); update(p, c, m + 1, e, i << 1 | 1);
	t[i] = t[i << 1] + t[i << 1 | 1];
}
ll query() { return t[1].ret; }

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> S >> U;
	N = strlen(S);
	init();
	std::cout << query() << '\n';
	for (int i = 0; i < U; ++i) {
		std::cin >> P >> C;
		update(P - 1, C);
		std::cout << query() << '\n';
	}
}