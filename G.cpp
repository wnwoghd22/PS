#include <iostream>
#include <cstring>
#include <queue>

const int LEN = 1e5 + 1;
int N, Q, p[LEN], checked[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return false;
	if (checked[a] || checked[b]) {
		checked[a] = checked[b] = 1;
		return false;
	}
	if (a < b) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return true;
}

struct Info {
	int u, size;
	bool operator<(const Info& r) const {
		if (size == r.size) return u > r.u;
		return size < r.size;
	}
};
std::priority_queue<Info> pq;

int main() {
	std::cin >> N >> Q;
	memset(p, -1, sizeof p);
	for (int i = 1; i <= N; ++i) pq.push({ i, 1 });
	for (int i = 0, q, u, v; i < Q; ++i) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> u >> v;
			bool is_tree = join(u, v);
			if (is_tree) {
				int j = find(u);
				pq.push({ j, -p[j] });
			}
			else {
				checked[find(u)] = true;
			}
		}
		if (q == 2) {
			while (pq.size()) {
				u = pq.top().u; pq.pop();
				if (find(u) != u) continue;
				u = find(u);
				if (checked[u]) continue;
				std::cout << u << '\n';
				checked[u] = true;
				break;
			}
		}
	}
}