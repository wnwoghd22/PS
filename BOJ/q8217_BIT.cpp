#include <iostream>
#include <vector>
#include <cstring>

typedef long long ll;
const int LEN = 300'001;

int N, M, Q;

ll fenwick[LEN];
ll get(int i) {
	ll result = 0;
	while (i > 0) {
		result += fenwick[i];
		i -= i & -i;
	}
	return result;
}
void update(int i, ll d) {
	while (i <= M) {
		fenwick[i] += d;
		i += i & -i;
	}
}
void update(int l, int r, ll d) {
	update(l, d);
	update(r + 1, -d);
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

		memset(fenwick, 0, sizeof fenwick);
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

