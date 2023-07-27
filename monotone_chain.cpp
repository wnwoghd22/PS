#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 1e5;
const int INF = 1e9;

struct Pos {
	int x, y;
	bool operator<(const Pos& r) const {
		return x == r.x ? y < r.y : x < r.x;
	}
} pos[LEN], hull[LEN];

ll cross(const Pos& p1, const Pos& p2, const Pos& p3) {
	return p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p3.x * p2.y - p2.x * p1.y - p1.x * p3.y;
}

int N;

int lenX = -1;
int posX[LEN];
int max[LEN];
int min[LEN];

int sp;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;

	for (int i = 0; i < N; ++i) {
		std::cin >> pos[i].x >> pos[i].y;
		max[i] = -INF; min[i] = INF;
	}
	std::sort(pos, pos + N);

	for (int i = 0, x = -INF; i < N; ++i) {
		if (x ^ pos[i].x) posX[++lenX] = x = pos[i].x;
		min[lenX] = std::min(min[lenX], pos[i].y);
		max[lenX] = std::max(max[lenX], pos[i].y);
	}
	hull[sp++] = { posX[0], min[0] };
	hull[sp++] = { posX[1], min[1] };

	for (int i = 2; i <= lenX; ++i) {
		Pos cur = { posX[i], min[i] };
		while (sp > 1) {
			if (cross(hull[sp - 2], hull[sp - 1], cur) <= 0) --sp;
			else break;
		}
		hull[sp++] = cur;
	}
	int bottom = sp;
	if (max[lenX] ^ min[lenX]) hull[sp++] = { posX[lenX], max[lenX] };
	hull[sp++] = { posX[lenX - 1], max[lenX - 1] };

	for (int i = lenX - 2; i >= 0; --i) {
		Pos cur = { posX[i], max[i] };
		while (sp > bottom) {
			if (cross(hull[sp - 2], hull[sp - 1], cur) <= 0) --sp;
			else break;
		}
		hull[sp++] = cur;
	}
	if (min[0] == max[0]) --sp;

	std::cout << sp;
}