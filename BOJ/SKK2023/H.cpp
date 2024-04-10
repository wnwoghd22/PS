#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

const int INF = 1e9;
const int LEN = 300'001;
struct Edge { 
	int l, r, k, i, j; 
	bool operator<(const Edge& rhs) const { return k < rhs.k; }
};
std::vector<int> posY;
std::vector<Edge> v;
int N, K, L, R, Ki;
int seg_min[LEN * 7], lazy[LEN * 7];
void propagate(int s, int e, int i) { // lazy propagation
	if (~lazy[i]) {
		seg_min[i] = lazy[i];
		if (s ^ e) {
			lazy[i << 1] = lazy[i];
			lazy[i << 1 | 1] = lazy[i];
		}
		lazy[i] = -1;
	}
}

void update_diff(int l, int r, int d, int s = 0, int e = posY.size() - 1, int i = 1) {
	propagate(s, e, i);

	if (e < l || r < s) return;
	if (l <= s && e <= r) {
		seg_min[i] = d;
		if (s ^ e) {
			lazy[i << 1] = d;
			lazy[i << 1 | 1] = d;
		}
		return;
	}
	int m = s + e >> 1;
	update_diff(l, r, d, s, m, i << 1);
	update_diff(l, r, d, m + 1, e, i << 1 | 1);

	seg_min[i] = std::min(seg_min[i << 1], seg_min[i << 1 | 1]);
}

int get_min(int l, int r, int s = 0, int e = posY.size() - 1, int i = 1) {
	propagate(s, e, i);

	if (e < l || r < s) return INF;
	if (l <= s && e <= r) return seg_min[i];

	int m = s + e >> 1;
	return std::min(get_min(l, r, s, m, i << 1), get_min(l, r, m + 1, e, i << 1 | 1));
}

int main() {
	freopen("input.txt", "r", stdin);

	std::cin >> N >> K;
	for (int i = 0; i < LEN * 7; ++i) seg_min[i] = INF, lazy[i] = -1;

	for (int i = 0; i < N; ++i) {
		std::cin >> L >> R >> Ki;
		posY.push_back(L); posY.push_back(R);
		v.push_back({ L, R, Ki });
	}
	std::sort(posY.begin(), posY.end());
	posY.erase(std::unique(posY.begin(), posY.end()), posY.end());
	for (Edge& e : v) {
		e.i = std::lower_bound(posY.begin(), posY.end(), e.l) - posY.begin();
		e.j = std::lower_bound(posY.begin(), posY.end(), e.r) - posY.begin();
		e.j -= 1;
	}
	std::sort(v.begin(), v.end());

	int ptr = 0, min;
	while (ptr < v.size() && v[ptr].k == 1) {
		update_diff(v[ptr].i, v[ptr].j, 0);
		++ptr;
	}

	for (int k = 2; k < K; ++k) {
		while (ptr < v.size() && v[ptr].k == k) {
			min = get_min(v[ptr].i, v[ptr].j);
			if (min < INF)
				update_diff(v[ptr].i, v[ptr].j, min + 1);
			++ptr;
		}
	}

	min = -1;
	while (ptr < v.size() && v[ptr].k == K) {
		Ki = get_min(v[ptr].i, v[ptr].j) + 1;
		if (Ki < INF) {
			if (!~min || Ki < min) min = Ki;
		}
		++ptr;
	}
	if (K == 1) min = 0;
	std::cout << min;
}