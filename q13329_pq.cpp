#include <iostream>
#include <algorithm>
#include <queue>

typedef long long ll;
const int LEN = 100'001;

struct Pos {
	ll x, y;
	int idx, d;
	bool operator<(const Pos& r) const { return y * r.x > r.y * x; }
} cur, pos[LEN << 1];

ll cross(const Pos& d1, const Pos& d2, const Pos& d3, const Pos& d4) { return (d2.x - d1.x) * (d4.y - d3.y) - (d2.y - d1.y) * (d4.x - d3.x); }

bool popped[LEN];

struct Segment {
	Pos l, r;
	int idx;
	bool operator<(const Segment& rhs) const {
		// if (idx == rhs.idx) return 0;
		if (popped[idx]) return 0;
		if (popped[rhs.idx]) return 1;
		if (l < rhs.l) return cross(r, l, l, rhs.l) > 0;
		else return cross(rhs.r, rhs.l, rhs.l, l) < 0;
	}
} segments[LEN];

std::priority_queue<Segment> pq;
int N, M, K, checked[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		segments[i].idx = i;
		std::cin >> M >> segments[i].l.x >> segments[i].l.y;
		segments[i].r = segments[i].l;
		for (int j = 1; j < M; ++j) {
			std::cin >> cur.x >> cur.y;
			if (cur < segments[i].l) segments[i].l = cur;
			if (segments[i].r < cur) segments[i].r = cur;
		}
		pos[i << 1] = segments[i].l; pos[i << 1].d = 1; pos[i << 1].idx = i;
		pos[i << 1 | 1] = segments[i].r; pos[i << 1 | 1].d = -1; pos[i << 1 | 1].idx = i;
	}
	/*for (int i = 0; i < N; ++i) {
		std::cout << segments[i].idx << ' ';
		std::cout << segments[i].l.x << ' ' << segments[i].l.y << ' ';
		std::cout << segments[i].r.x << ' ' << segments[i].r.y << '\n';
	}*/

	std::sort(pos, pos + N * 2);
	// std::cout << "events\n";
	// for (int i = 0; i < N * 2; ++i) {
	// 	std::cout << pos[i].x << ' ' << pos[i].y << ' ' << pos[i].idx << ' ' << pos[i].d << '\n';
	// }

	for (int i = 0; i < N * 2; ++i) {
		// std::cout << i << ' ';
		// if (s.size()) std::cout << ((*s.begin()) < segments[pos[i].idx]) << '\n';
		if (~pos[i].d) pq.push(segments[pos[i].idx]);
		else popped[pos[i].idx] = 1;
		while (pq.size() && popped[pq.top().idx]) pq.pop();
		if (pq.size()) 
			// std::cout << pq.top().idx << ' ', 
			K += !checked[pq.top().idx]++;
	}
	std::cout << N - K;
}