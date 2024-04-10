#include <iostream>
#include <algorithm>

const int LEN = 20'000;
const int INF = 1e9 + 7;
const int RIGHT = 1;
const int LEFT = 2;
const int UP = 4;
const int DOWN = 8;

struct Pos { int x, y; } robots[5], pos[LEN];
int dir[LEN];
int N;

bool check(const Pos& p) {
	int l = -1, r = -1, u = -1, d = -1;
	for (int i = 0; i < N; ++i) {
		Pos cur = pos[i], nxt = pos[(i + 1) % N];
		if (dir[i] == LEFT) {
			if (cur.y < p.y && cur.x > p.x) {
				if (nxt.x < p.x || nxt.x == p.x && dir[(i + 1) % N] == DOWN)
					return false;
			}
			if (cur.y >= p.y && cur.x >= p.x && nxt.x < p.x) {
				if (!~u || cur.y > pos[u].y) u = i;
			}
		}
		if (dir[i] == RIGHT) {
			if (cur.y > p.y && cur.x < p.x) {
				if (nxt.x > p.x || nxt.x == p.x && dir[(i + 1) % N] == UP)
					return false;
			}
			if (cur.y <= p.y && cur.x <= p.x && nxt.x > p.x) {
				if (!~d || cur.y < pos[d].y) d = i;
			}
		}
		if (dir[i] == UP) {
			if (cur.x < p.x && cur.y < p.y) {
				if (nxt.y > p.y || nxt.y == p.y && dir[(i + 1) % N] == LEFT)
					return false;
			}
			if (cur.x >= p.x && cur.y <= p.y && nxt.y > p.y) {
				if (!~r || cur.x > pos[r].x) r = i;
			}
		}
		if (dir[i] == DOWN) {
			if (cur.x > p.x && cur.y > p.y) {
				if (nxt.y < p.y || nxt.y == p.y && dir[(i + 1) % N] == RIGHT)
					return false;
			}
			if (cur.x <= p.x && cur.y >= p.y && nxt.y < p.y) {
				if (!~l || cur.x < pos[l].x) l = i;
			}
		}
	}
	for (int i = d, bound = -1, pivotY = pos[i].y; i != r; i = (i + 1) % N) {
		if (dir[i] == DOWN) bound = pos[i].x;
		if (dir[i] == UP) pivotY = std::max(pivotY, pos[(i + 1) % N].y);
		if (dir[i] == RIGHT) {
			if (pos[i].y < pivotY)
				bound = pos[(i + 1) % N].x;
		}
		if (dir[i] == LEFT) {
			if ((i + 1) % N == r) continue;
			if (pos[(i + 1) % N].x < bound)
				return false;
		}
	}
	for (int i = r, bound = -1, pivotX = pos[i].x; i != u; i = (i + 1) % N) {
		if (dir[i] == RIGHT) bound = pos[i].y;
		if (dir[i] == LEFT) pivotX = std::min(pivotX, pos[(i + 1) % N].x);
		if (dir[i] == UP) {
			if (pos[i].x > pivotX)
				bound = pos[(i + 1) % N].y;
		}
		if (dir[i] == DOWN) {
			if ((i + 1) % N == u) continue;
			if (pos[(i + 1) % N].y < bound)
				return false;
		}
	}
	for (int i = u, bound = INF, pivotY = pos[i].y; i != l; i = (i + 1) % N) {
		if (dir[i] == UP) bound = pos[i].x;
		if (dir[i] == DOWN) pivotY = std::min(pivotY, pos[(i + 1) % N].y);
		if (dir[i] == LEFT) {
			if (pos[i].y > pivotY)
				bound = pos[(i + 1) % N].x;
		}
		if (dir[i] == RIGHT) {
			if ((i + 1) % N == l) continue;
			if (pos[(i + 1) % N].x > bound)
				return false;
		}
	}
	for (int i = l, bound = INF, pivotX = pos[i].x; i != d; i = (i + 1) % N) {
		if (dir[i] == LEFT) bound = pos[i].y;
		if (dir[i] == RIGHT) pivotX = std::max(pivotX, pos[(i + 1) % N].x);
		if (dir[i] == DOWN) {
			if (pos[i].x < pivotX)
				bound = pos[(i + 1) % N].y;
		}
		if (dir[i] == UP) {
			if ((i + 1) % N == d) continue;
			if (pos[(i + 1) % N].y > bound)
				return false;
		}
	}
	return true;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> pos[i].x >> pos[i].y;
	for (int i = 0; i < N; ++i) {
		Pos cur = pos[i], nxt = pos[(i + 1) % N];
		if (cur.x > nxt.x) dir[i] = LEFT;
		if (cur.x < nxt.x) dir[i] = RIGHT;
		if (cur.y > nxt.y) dir[i] = DOWN;
		if (cur.y < nxt.y) dir[i] = UP;
	}
	for (int i = 0; i < 5; ++i) {
		std::cin >> robots[i].x >> robots[i].y;
		if (check(robots[i])) std::cout << "YES\n";
		else std::cout << "NO\n";
	}

}