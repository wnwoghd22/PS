#include <iostream>
#include <cstring>
#include <queue>

const int LEN = 10'001;
int T, S, L;
int p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
int join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return 1;
}

struct E {
	int u, v, w;
	bool operator<(const E& o) const {
		return w < o.w;
	}
};

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	for (int x = 1; x <= T; ++x) {
		std::cin >> S >> L;
		memset(p, -1, sizeof p);
		std::priority_queue<E> pq;
		int d = 0, m = 0, cnt = S - 1;
		for (int i = 0, u, v, w; i < L; ++i) {
			std::cin >> u >> v >> w;
			pq.push({ u, v, w });
			d += w;
		}
		while (cnt) {
			E e = pq.top(); pq.pop();
			if (join(e.u, e.v)) {
				d -= e.w;
				cnt--;
			}
			else m = std::max(m, e.w);
		}
		if (pq.size()) m = std::max(m, pq.top().w);

		std::cout << "Case #" << x << ": " << d << ' ' << m << '\n';
	}

}