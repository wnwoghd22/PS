#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>

typedef long long ll;
const int LEN = 2e5 + 5;

int N, len, T;
ll fenwick[LEN];
ll sum(int i) {
	ll result = 0;
	while (i > 0) {
		result += fenwick[i];
		i -= i & -i;
	}
	return result;
}
void update(int i, ll d) {
	while (i <= len) {
		fenwick[i] += d;
		i += i & -i;
	}
}
void update(int l, int r, ll d) {
	update(l, d);
	update(r, d);
}

int p[LEN], color[LEN];
std::set<int> verts[LEN << 2];
int seg_v[LEN << 2];
int maxY[LEN];
int seg_pos[LEN << 2];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return false;
	if (maxY[a] > maxY[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return true;
}
int add_line(int l, int r, int idx, int s = 1, int e = N * 2, int i = 1) {
	if (e < l || r < s) return 0;
	if (l <= s && e <= r) {
		if (~seg_v[i]) join(idx, seg_v[i]);
		for (const int& v : verts[i]) {
			join(idx, v);
			if (!~seg_v[i] || maxY[v] > maxY[seg_v[i]])
				seg_v[i] = v;
		}
		verts[i].clear();
		return seg_pos[i];
	}
	int m = s + e >> 1;
	return add_line(l, r, idx, s, m, i << 1) + add_line(l, r, idx, m + 1, e, i << 1 | 1);
}
void update_pos(int x, int d, int idx, int s = 1, int e = N * 2, int i = 1) {
	if (x < s || e < x) return;

	if (d > 0) verts[i].insert(idx);
	else if (d < 0) {
		verts[i].erase(idx);
		if (seg_v[i] == idx) seg_v[i] = -1;
	}

	if (s == e) {
		seg_pos[i] += d;
		return;
	}
	int m = s + e >> 1;
	update_pos(x, d, idx, s, m, i << 1);
	update_pos(x, d, idx, m + 1, e, i << 1 | 1);
	seg_pos[i] = seg_pos[i << 1] + seg_pos[i << 1 | 1];
}

struct Query {
	int y, l, r, d, i;
	bool operator<(const Query& q) const { return y < q.y; }
} q[LEN];

ll W, B;
ll cntB, cntW;
ll mergeB, mergeW;

int main() {
	freopen("input.txt", "r", stdin);
	std::cin.tie(0)->sync_with_stdio(0);

	std::cin >> N >> T; 
	len = N << 1 | 1;
	for (int i = 0, l, r, u, d; i < N; ++i) {
		std::cin >> l >> d >> r >> u;
		q[i << 1] = { d, l, r, 1, i + 1 };
		q[i << 1 | 1] = { u, l, r, -1, i + 1 };
		maxY[i + 1] = u;
	}
	memset(p, -1, sizeof p);
	memset(seg_v, -1, sizeof seg_v);
	std::sort(q, q + 2 * N);
	for (ll i = 0, l, r, cw, cb, mw, mb, rw, rb, cnt; i < 2 * N; ++i) {
		if (q[i].d == 1) { // add query
			update(q[i].l, q[i].r, q[i].d);
			add_line(q[i].l, q[i].r, q[i].i);
			update_pos(q[i].l, 1, q[i].i);
			update_pos(q[i].r, 1, q[i].i);
			cnt = sum(len) + 1;
			cw = cnt + 1 >> 1;
			cb = cnt - cw;
			l = sum(q[i].l);
			r = sum(q[i].r);
			if (l & 1) { // BWBW...
				rb = (r - l + 1) / 2;
				rw = r - l - rb;
			}
			else {
				rw = (r - l + 1) / 2;
				rb = r - l - rw;
			}
			mw = cw - rw; mb = cb - rb;
			cntW += cw; cntB += cb;
			mergeW += mw; mergeB += mb;
		}
		else {
			cnt = sum(len) + 1;
			cw = cnt + 1 >> 1;
			cb = cnt - cw;
			l = sum(q[i].l);
			r = sum(q[i].r);
			if (l & 1) { // BWBW...
				rb = (r - l + 1) / 2;
				rw = r - l - rb;
			}
			else {
				rw = (r - l + 1) / 2;
				rb = r - l - rw;
			}
			mw = cw - rw; mb = cb - rb;
			update(q[i].l, q[i].r, q[i].d);
			add_line(q[i].l, q[i].r, q[i].i);
			update_pos(q[i].l, -1, q[i].i);
			update_pos(q[i].r, -1, q[i].i);
			cnt = sum(len) + 1;
			cw = cnt + 1 >> 1;
			cb = cnt - cw;
			if (r - l == 1) // cover top event
				color[q[i].i] = l & 1;
			cntW += cw; cntB += cb;
			mergeW += mw; mergeB += mb;
		}

		// std::cout << cw << ' ' << cb << ' ' << mw << ' ' << mb << '\n';
	}
	W = cntW - mergeW + 1;
	B = cntB - mergeB;

	for (int i = 1; i <= N; ++i) {
		if (i == find(i))
			(color[i] ? W : B)++;
	}

	if (T == 1) std::cout << W + B;
	else std::cout << W << ' ' << B;
}