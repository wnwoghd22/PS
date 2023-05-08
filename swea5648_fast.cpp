#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>

enum Slope { LR, UD, LU, LD, RU, RD, };
enum Dir { U, D, L, R, };

const int LEN = 1001;
std::map<int, int> slopes[6];
struct Atom {
	int x, y, k, d, stamp;
	int ptr[6]; // node index of linked list
	bool operator<(const Atom& r) const {
		if (y == r.y) return x < r.x;
		return y > r.y;
	}
} atoms[LEN];
struct Node {
	int bf, nx;
	int i;
} ls[LEN * 6];
int ni;
struct Collision {
	int bf, nx, stamp;
	bool operator<(const Collision& r) const { return stamp > r.stamp; }
};
std::priority_queue<Collision> pq;

int dist(int a, int b) { // manhatten
	return abs(atoms[a].x - atoms[b].x) + abs(atoms[a].y - atoms[b].y);
}

int adj[4][4] = {
	//	 U   D   L   R
		-1, UD, LU, RU, // U
		UD, -1, LD, RD, // D
		LU, LD, -1, LR, // L
		RU, RD, LR, -1  // R
};

int get_key(int slope, int i) {
	switch (slope) {
	case LR: return atoms[i].y;
	case UD: return atoms[i].x;
	case LU: case RD: return atoms[i].y - atoms[i].x;
	case RU: case LD: return atoms[i].y + atoms[i].x;
	}
}

bool isCollide(int slope, int bf, int nx) {
	if (!~bf || !~nx) return false;
	switch (slope) {
	case LR: return atoms[bf].d == L && atoms[nx].d == R;
	case UD: return atoms[bf].d == D && atoms[nx].d == U;
	case LU: return atoms[bf].d == L && atoms[nx].d == U;
	case LD: return atoms[bf].d == D && atoms[nx].d == L;
	case RU: return atoms[bf].d == R && atoms[nx].d == U;
	case RD: return atoms[bf].d == D && atoms[nx].d == R;
	}
}

void push(int slope, int i) {
	int key = get_key(slope, i);
	atoms[i].ptr[slope] = ni;
	ls[ni].i = i;
	if (slopes[slope].find(key) != slopes[slope].end()) {
		int bf = slopes[slope][key];
		int bi = ls[bf].i;
		ls[bf].nx = ni;
		ls[ni].bf = bf;
		if (isCollide(slope, bi, i)) {
			// std::cout << "collide: " << i << ", " << bi << '\n';
			pq.push({ bi, i, dist(i, bi) });
		}
	}
	slopes[slope][key] = ni++; // move head
}

void push(int i, int x, int y, int k, int d) {
	// atoms[i] = { x, y, k, d };
	switch (d) {
	case U: push(UD, i); push(LU, i); push(RU, i); break;
	case D: push(UD, i); push(LD, i); push(RD, i); break;
	case L: push(LR, i); push(LU, i); push(LD, i); break;
	case R: push(LR, i); push(RU, i); push(RD, i); break;
	}
}

void pop(int i) {
	for (int s = 0; s < 6; ++s) {
		if (!~atoms[i].ptr[s]) continue;
		Node n = ls[atoms[i].ptr[s]];
		if (~n.bf) ls[n.bf].nx = n.nx;
		if (~n.nx) ls[n.nx].bf = n.bf;
		if (~n.bf && ~n.nx && isCollide(s, ls[n.bf].i, ls[n.nx].i)) {
			pq.push({ ls[n.bf].i, ls[n.nx].i, dist(ls[n.bf].i, ls[n.nx].i) });
		}
	}
}

int N;

int solve() {
	std::cin >> N;
	ni = 0;
	memset(atoms, -1, sizeof atoms);
	memset(ls, -1, sizeof ls);
	for (int i = 0; i < 6; ++i) slopes[i].clear();
	for (int i = 0, x, y, k, d; i < N; ++i) {
		std::cin >> atoms[i].x >> atoms[i].y >> atoms[i].d >> atoms[i].k;
		// atoms[i] = { x, y, k, d };
	}
	std::sort(atoms, atoms + N);
	for (int i = 0, x, y, k, d; i < N; ++i) {
		push(i, atoms[i].x, atoms[i].y, atoms[i].k, atoms[i].d);
	}
	while (pq.size()) {
		Collision c = pq.top(); pq.pop(); // fastest collision
		if (!~atoms[c.bf].stamp && !~atoms[c.nx].stamp) { // new collision
			// std::cout << "collide" << '\n';
			atoms[c.bf].stamp = atoms[c.nx].stamp = c.stamp;
			pop(c.bf); pop(c.nx);
		}
		else if (~atoms[c.bf].stamp && ~atoms[c.nx].stamp) { // invalid
			// std::cout << "not collide" << '\n';
			continue;
		}
		else if (!~atoms[c.bf].stamp) {
			if (atoms[c.nx].stamp == c.stamp) { // collides at one point
				// std::cout << "collide bf" << '\n';
				atoms[c.bf].stamp = c.stamp;
				pop(c.bf);
			}
		}
		else if (!~atoms[c.nx].stamp) {
			if (atoms[c.bf].stamp == c.stamp) { // collides at one point
				// std::cout << "collide nx" << '\n';
				atoms[c.nx].stamp = c.stamp;
				pop(c.nx);
			}
		}
	}
	int result = 0;
	for (int i = 0; i < N; ++i) {
		// std::cout << atoms[i].stamp << '\n';
		if (~atoms[i].stamp)
			result += atoms[i].k;
	}
	return result;
}

int main() {
	// freopen("input.txt", "r", stdin);
	int t, T;
	std::cin >> T;
	for (t = 1; t <= T; ++t) {
		std::cout << '#' << t << ' ' << solve() << '\n';
	}
}