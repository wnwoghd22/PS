#include <iostream>
#include <algorithm>
#include <cstring>

typedef long long ll;
const int LEN = 400;
const int INF = 1e9;

struct Pos {
	ll x, y;
	bool operator<(const Pos& r) const {
		return x == r.x ? y < r.y : x < r.x;
	}
} pos[LEN], hull[LEN];

ll cross(const Pos& p1, const Pos& p2, const Pos& p3) {
	return p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p3.x * p2.y - p2.x * p1.y - p1.x * p3.y;
}

int N, K;

int lenX = -1;
int posX[LEN];
ll max[LEN];
ll min[LEN];

int sp;

ll dp[10][LEN][LEN];

ll f(int s, int e, int k) {
	if (s + 1 >= e || !k) return 0;
	ll& ref = dp[k][s][e];
	if (~ref) return ref;

	ref = 0;
	for (int m = s + 1; m < e; ++m) {
		ref = std::max(ref, cross(hull[s], hull[m], hull[e]) + f(m, e, k - 1));
	}
	return ref;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> K;

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

	memset(dp, -1, sizeof dp);
	
	ll result = 0;
	for (int i = 0; i < sp; ++i) {
		for (int j = i + 1; j < sp; ++j)
			result = std::max(result, f(i, j, K - 2));
	}
	std::cout << (result >> 1) << '.';
	std::cout << 5 * (result & 1);
}