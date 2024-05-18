#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

const int LEN = 400'001;
const int INF = 1e9 + 7;

int N, Q, cur[LEN];
std::vector<int> px;
std::priority_queue<int> pq[LEN << 2];
int t[LEN << 2];
std::vector<int> ret[LEN];

void push(int x, int idx, int s = 0, int e = px.size() - 1, int i = 1) {
	if (x < px[s] || px[e] < x) return;
	if (s == e) {
		pq[i].push(-idx);
		t[i] = -pq[i].top();
		return;
	}
	int m = s + e >> 1;
	push(x, idx, s, m, i << 1);
	push(x, idx, m + 1, e, i << 1 | 1);
	t[i] = std::min(t[i << 1], t[i << 1 | 1]);
}

void pop(int x, int s = 0, int e = px.size() - 1, int i = 1) {
	if (x < px[s] || px[e] < x) return;
	if (s == e) {
		pq[i].pop();
		t[i] = pq[i].size() ? -pq[i].top() : INF;
		return;
	}
	int m = s + e >> 1;
	pop(x, s, m, i << 1);
	pop(x, m + 1, e, i << 1 | 1);
	t[i] = std::min(t[i << 1], t[i << 1 | 1]);
}

int query(int l, int r, int s = 0, int e = px.size() - 1, int i = 1) {
	if (r < px[s] || px[e] < l) return INF;
	if (l <= px[s] && px[e] <= r) return t[i];
	int m = s + e >> 1;
	return std::min(query(l, r, s, m, i << 1), query(l, r, m + 1, e, i << 1 | 1));
}

struct Laser {
	int x, y, i;
	bool operator<(const Laser& o) const { return y < o.y; }
} lasers[LEN];

struct Wall {
	int l, r, h, v, i;
	bool operator<(const Wall& o) const { return h == o.h ? l < o.l : h < o.h; }
} walls[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> Q;

	for (int i = 0; i < N; ++i) {
		std::cin >> walls[i].l >> walls[i].r >> walls[i].h >> walls[i].v;
		walls[i].i = i + 1;
		px.push_back(walls[i].v);
	}

	for (int i = 0; i < Q; ++i) {
		std::cin >> lasers[i].x >> lasers[i].y;
		lasers[i].i = i + 1;
		px.push_back(lasers[i].x);
	}

	std::sort(walls, walls + N);
	std::sort(lasers, lasers + Q);
	std::sort(px.begin(), px.end());
	px.erase(std::unique(px.begin(), px.end()), px.end());

	for (int i = 0; i < LEN; ++i) t[i] = INF;

	for (int i = 0, j = 0; i < N;) {
		int y = walls[i].h;
		while (j < Q && lasers[j].y <= y) {
			push(lasers[j].x, lasers[j].i);
			cur[lasers[j].i] = lasers[j].x;
			j++;
		}
		std::vector<int> updated;
		while (i < N && walls[i].h == y) {
			int idx = query(walls[i].l, walls[i].r);
			if (idx != INF) {
				ret[idx].push_back(walls[i].i);
				pop(cur[idx]);
				cur[idx] = walls[i].v;
				updated.push_back(idx);
			}
			i++;
		}
		for (const int& idx : updated) {
			push(cur[idx], idx);
		}
	}
	for (int i = 1; i <= Q; ++i) {
		std::cout << ret[i].size() << '\n';
		if (ret[i].size()) {
			for (const int& e : ret[i]) std::cout << e << ' ';
			std::cout << '\n';
		}
	}
}