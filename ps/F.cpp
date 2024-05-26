#include <iostream>
#include <cstring>

const int LEN = 1e5 + 1;

int N, Q;
int p[LEN];

int c[LEN];
int not_bi[LEN];
int group[LEN];

int R[LEN];
int B[LEN];

struct SegMax{
	int t[LEN << 2];
	int cnt[LEN];
	void update(int x, int d, int s = 1, int e = N, int i = 1) {
		if (x < s || e < x) return;
		if (s == e) {
			cnt[x] = d;
			t[i] = x;
			return;
		}
		int m = s + e >> 1;
		update(x, d, s, m, i << 1);
		update(x, d, m + 1, e, i << 1 | 1);
		t[i] = cnt[t[i << 1]] >= cnt[t[i << 1 | 1]] ? t[i << 1] : t[i << 1 | 1];
	}
	int get_max_index() { return t[1]; }

} red, blue;

int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
int get_cnt(int i) { return -p[i]; }
void flip(int i) {
	std::cout << "flip find: " << find(i) << '\n';
	int gi = group[find(i)];
	std::cout << "flip group " << gi << '\n';
	int gr = R[gi];
	int gb = B[gi];
	std::cout << "flip: " << gr << ' ' << gb << '\n';
	int cr = ~gr ? get_cnt(gr) : 0;
	int cb = ~gb ? get_cnt(gb) : 0;
	std::cout << "count: " << cr << ' ' << cb << '\n';
	if (~gr) c[gr] ^= 1;
	if (~gb) c[gb] ^= 1;
	std::swap(R[gi], B[gi]);
	red.update(gi, cb);
	blue.update(gi, cr);
}

void join_group(int u, int v) {
	int gu = group[u];
	int gv = group[v];
	if (gu > gv) std::swap(gu, gv);

	int ur = R[gu], ub = B[gu];
	int vr = R[gv], vb = B[gv];
	std::cout << gu << ' ' << gv << '\n';
	std::cout << ur << ' ' << ub << ' ' << vr << ' ' << vb << '\n';

	if (~ur) group[ur] = gu;
	if (~ub) group[ub] = gu;
	if (~vr) group[vr] = gu;
	if (~vb) group[vb] = gu;

	if (not_bi[gu] || not_bi[gv]) {
		not_bi[gu] = not_bi[gv] = 1;
		if (~ur) p[vr] = ur;
		else R[gu] = vr;

		if (~ub) p[vb] = ub;
		else B[gu] = vb;

		red.update(gu, 0);
		blue.update(gu, 0);
		red.update(gv, 0);
		blue.update(gv, 0);
		return;
	}

	int gur = ~ur ? get_cnt(ur) : 0;
	int gub = ~ub ? get_cnt(ub) : 0;
	int gvr = ~vr ? get_cnt(vr) : 0;
	int gvb = ~vb ? get_cnt(vb) : 0;

	red.update(gv, 0);
	blue.update(gv, 0);

	if (c[u] == c[v]) { // need to swap
		std::cout << "group " << gu << " cnt: " << gur + gub << '\n';
		std::cout << "group " << gv << " cnt: " << gvr + gvb << '\n';
		if (gur + gub > gvr + gvb) flip(gv);
		else flip(gu);
	}
	
	vr = R[gv], vb = B[gv];
	
	if (~R[gu]) {
		if (~vr) {
			p[ur] += p[vr];
			p[vr] = ur;
			red.update(gu, get_cnt(ur));
		}
	}
	else {
		R[gu] = ur = vr;
		red.update(gu, get_cnt(ur));
	}

	if (~B[gu]) {
		if (~vb) {
			p[ub] += p[vb];
			p[vb] = ub;
			blue.update(gu, get_cnt(ur));
		}
	}
	else {
		B[gu] = ub = vb;
		blue.update(gu, get_cnt(ub));
	}
}

int join(int u, int v) {
	u = find(u), v = find(v);
	if (u == v) { // same cc, same color
		not_bi[u] = 1;
		int gu = group[u];
		red.update(R[gu], 0);
		red.update(B[gu], 0);
		return -1;
	}
	if (group[u] == group[v]) { // nothing happens
		return 0;
	}

	join_group(u, v);
	return 1;
}


int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> Q;
	for (int i = 1; i <= N; ++i) {
		std::cin >> c[i];
		group[i] = i;
		if (!c[i]) {
			red.update(i, 1);
			R[i] = i;
			B[i] = -1;
		}
		else {
			blue.update(i, 1);
			B[i] = i;
			R[i] = -1;
		}
	}
	memset(p, -1, sizeof p);

	for (int i = 0, q, u, v; i < Q; ++i) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> u >> v;
			join(u, v);
		}
		if (q == 2) {
			std::cin >> u;
			flip(u);
		}
		if (q == 3) {
			std::cin >> u;
			if (!u) std::cout << red.get_max_index() << '\n';
			else std::cout << blue.get_max_index() << '\n';
		}
	}
}