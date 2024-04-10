#include <iostream>
#include <algorithm>

const int LEN = 100'001;

int p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return false;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return true;
}
int size(int i) { return -p[find(i)]; }

struct Edge {
	int a, b, c;
	bool operator<(const Edge& r) const { return c < r.c; }
} edges[LEN];
struct Query {
	int x, y;
} queries[LEN];
int l[LEN], r[LEN], c[LEN], v[LEN];
int ptr[LEN], sp, idx[LEN], next[LEN];

int N, M, Q, R;

int main() {
	std::cin >> N >> M;
	for (int i = 0; i < M; ++i) 
		std::cin >> edges[i].a >> edges[i].b >> edges[i].c;
	std::sort(edges, edges + M);
	
	std::cin >> Q;
	for (int i = 0; i < Q; ++i) {
		std::cin >> queries[i].x >> queries[i].y;
		l[i] = 0; r[i] = M;
	}
	while (1) {
		R = sp = 0;
		memset(p, -1, sizeof p);
		memset(ptr, -1, sizeof ptr);
		for (int i = 0; i < Q; ++i) {
			if (l[i] < r[i]) {
				++R;
				int m = l[i] + r[i] >> 1;
				idx[sp] = i; next[sp] = ptr[m];
				ptr[m] = sp++;
			}
		}
		if (!R) break;

		for (int m = 0; R && m < M; ++m) {
			join(edges[m].a, edges[m].b);

			int cur = ptr[m];
			while (~cur) {
				--R;
				int qi = idx[cur];
				if (find(queries[qi].x) == find(queries[qi].y)) {
					r[qi] = m;
					c[qi] = edges[m].c;
					v[qi] = size(queries[qi].x);
				}
				else l[qi] = m + 1;

				cur = next[cur];
			}
		}
	}
	for (int i = 0; i < Q; ++i) {
		if (c[i]) std::cout << c[i] << ' ' << v[i] << '\n';
		else std::cout << "-1\n";
	}
}