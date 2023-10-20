#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;
const int LEN = 100'001;

struct Pos {
	ll x, y;
	bool operator<(const Pos& r) const { return y * r.x > r.y * x; }
	bool operator<=(const Pos& r) const { return  y * r.x >= r.y * x; }
} pos[LEN];

ll cross(const Pos& d1, const Pos& d2, const Pos& d3, const Pos& d4) { return (d2.x - d1.x) * (d4.y - d3.y) - (d2.y - d1.y) * (d4.x - d3.x); }
void monotone_chain(std::vector<Pos>& H, int s, int e) {
	if (e - s <= 1) {
		for (int i = s; i <= e; ++i) H.push_back(pos[i]);
		return;
	}
	for (int i = s; i <= e; ++i) {
		while (H.size() > 1 && cross(H[H.size() - 2], H[H.size() - 1], H[H.size() - 1], pos[i]) <= 0) {
			H.pop_back();
		}
		H.push_back(pos[i]);
	}
	H.pop_back();
	int k = H.size() + 1;
	for (int i = e - 1; i >= s; --i) {
		while (H.size() > k && cross(H[H.size() - 2], H[H.size() - 1], H[H.size() - 1], pos[i]) <= 0) {
			H.pop_back();
		}
		H.push_back(pos[i]);
	}
	H.pop_back();
}

std::vector<Pos> seg[LEN << 2];

void init(int s, int e, int i = 1) {
	if (s == e) {
		seg[i] = { pos[s] };
		return;
	}
	int m = s + e >> 1;
	init(s, m, i << 1); init(m + 1, e, i << 1 | 1);
	monotone_chain(seg[i], s, e);
}

bool ter_search(const Pos& p1, const Pos& p2, const std::vector<Pos>& hull) {
	int s = 0, e = hull.size() - 1, l, r;
	while (e - s >= 3) {
		l = (s * 2 + e) / 3;
		r = (s + e * 2) / 3;
		ll L = cross(p1, p2, p2, hull[l]);
		ll R = cross(p1, p2, p2, hull[r]);
		if (L < R) e = r;
		else s = l;
	}
	for (int i = s; i <= e; ++i) {
		if (cross(p1, p2, p2, hull[i]) <= 0)
			return true;
	}

	return false;
}

bool search(const Pos& l, const Pos& r, int s, int e, int i = 1) {
	if (r < pos[s] || pos[e] < l) return false;
	if (l <= pos[s] && pos[e] <= r) return ter_search(l, r, seg[i]);
	int m = s + e >> 1;
	return search(l, r, s, m, i << 1) || search(l, r, m + 1, e, i << 1 | 1);
}

int K, M;
Pos p1, p2;
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	std::cin.tie(0)->sync_with_stdio(0);

	std::cin >> K >> M;
	for (int i = 0; i < K; ++i) std::cin >> pos[i].x >> pos[i].y;
	std::sort(pos, pos + K);
	init(0, K - 1);

	while (M--) {
		std::cin >> p1.x >> p1.y >> p2.x >> p2.y;
		if (p2 < p1) std::swap(p1, p2);
		std::cout << (search(p1, p2, 0, K - 1) ? "Y\n" : "N\n");
	}
}