#include <iostream>
#include <vector>
#include <cstring>

typedef long long ll;
const int LEN = 300'001;

int N, M, Q;

ll seg_tree[LEN << 2];
void update(int l, int r, ll d, int s = 1, int e = M, int i = 1) {
	if (r < s || e < l) return;
	if (l <= s && e <= r) { seg_tree[i] += d; return; }
	int m = s + e >> 1;
	update(l, r, d, s, m, i << 1); update(l, r, d, m + 1, e, i << 1 | 1);
}
ll get(int x, int s = 1, int e = M, int i = 1) {
	if (x < s || e < x) return 0;
	if (s == e) return seg_tree[i];
	int m = s + e >> 1;
	return seg_tree[i] + get(x, s, m, i << 1) + get(x, m + 1, e, i << 1 | 1);
}

int ql[LEN], qr[LEN], qa[LEN];
int cnt, ptr[LEN], np[LEN], l[LEN], r[LEN], o[LEN], p[LEN];
std::vector<int> s[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	for (int i = 1; i <= M; ++i) {
		std::cin >> o[i];
		s[o[i]].push_back(i);
	}
	for (int j = 1; j <= N; ++j) std::cin >> p[j];

	std::cin >> Q;
	for (int u = 0; u < Q; ++u)
		std::cin >> ql[u] >> qr[u] >> qa[u];

	for (int i = 1; i <= N; ++i) r[i] = Q;

	while (1) {
		cnt = 0;
		memset(ptr, -1, sizeof ptr);
		for (int i = 1, m; i <= N; ++i) {
			if (l[i] < r[i]) {
				++cnt;
				m = l[i] + r[i] >> 1;
				np[i] = ptr[m]; ptr[m] = i;
			}
		}
		if (!cnt) break;

		memset(seg_tree, 0, sizeof seg_tree);
		for (int m = 0, j; m < Q; ++m) {
			if (ql[m] <= qr[m]) update(ql[m], qr[m], qa[m]);
			else update(1, qr[m], qa[m]), update(ql[m], M, qa[m]);

			j = ptr[m];
			while (~j) {
				ll sum = 0;
				for (const int& x : s[j]) {
					sum += get(x);
					if (sum >= p[j]) break;
				}

				if (sum >= p[j]) r[j] = m;
				else l[j] = m + 1;
				j = np[j];
			}
		}
	}
	for (int j = 1; j <= N; ++j) {
		if (r[j] == Q) std::cout << "NIE\n";
		else std::cout << r[j] + 1 << '\n';
	}
}

