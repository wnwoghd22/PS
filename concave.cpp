#include <iostream>

typedef long long ll;
const int LEN = 10'000;

struct Pos { int x, y; } t, p[LEN];

ll cross(const Pos& p1, const Pos& p2, const Pos& p3) { return (ll)(p2.x - p1.x) * (p3.y - p2.y) - (ll)(p2.y - p1.y) * (p3.x - p2.x); }
ll dot(const Pos& p1, const Pos& p2, const Pos& p3) { return (ll)(p2.x - p1.x) * (p3.x - p2.x) + (ll)(p2.y - p1.y) * (p3.y - p2.y); }
bool on_seg(const Pos& p1, const Pos& p2, const Pos& t) { return cross(p1, p2, t) == 0 && dot(p1, t, p2) >= 0; }
bool check_inner(const Pos& t, int n) {
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		Pos cur = p[i], nxt = p[(i + 1) % n];
		if (on_seg(cur, nxt, t)) return 1;
		if (cur.y == nxt.y) continue;
		if (cur.y > nxt.y) std::swap(cur, nxt);
		if (t.y < cur.y || t.y >= nxt.y) continue;
		if (cross(cur, nxt, t) > 0) cnt++;
	}
	return cnt & 1;
}

int N;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> p[i].x >> p[i].y;
	for (int i = 0; i < 3; ++i) {
		std::cin >> t.x >> t.y;
		std::cout << check_inner(t, N) << '\n';
	}
}