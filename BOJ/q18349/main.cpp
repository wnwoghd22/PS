#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cassert>
#include <vector>
#include <queue>
#include <deque>

#include "lct_module.h"
#include "lcp_module.h"
#include "kdt_module.h"

typedef long long ll;
typedef long double ld;
//typedef double ld;
typedef std::vector<int> Vint;
typedef std::vector<ll> Vll;
const ld INF = 1e18;
const ll LINF = 1e18;
const ld TOL = 1e-9;
const ld PI = acos(-1);
const int LEN = 9e4;
inline ll sqr(const int& a) { return (ll)a * a; }
inline int sign(const ll& x) { return x < 0 ? -1 : !!x; }
inline int sign(const ld& x) { return x < -TOL ? -1 : x > TOL; }
inline bool zero(const ld& x) { return !sign(x); }
inline bool eq(const ld& x, const ld& y) { return zero(x - y); }
inline ld sq(const ld& x) { return x * x; }
inline ll sq(const ll& x) { return x * x; }
inline ld norm(ld th) { while (th < 0) th += 2 * PI; while (sign(th - 2 * PI) >= 0) th -= 2 * PI; return th; }
inline ld fit(const ld& x, const ld& lo = 0, const ld& hi = 1) { return std::min(hi, std::max(lo, x)); }
inline ll gcd(ll a, ll b) { while (b) { ll tmp = a % b; a = b; b = tmp; } return a; }

int N, M, T, Q, Q1, Q2;
Vint DT[LEN];//delaunay triangle
std::vector<std::string> name;

#define INT_MAX 100000000

struct Pii {
	ll x, y; int i;
	Pii(ll x_ = 0, ll y_ = 0, int i_ = 0) : x(x_), y(y_), i(i_) {}
	Pii operator - (const Pii& p) const { return { x - p.x, y - p.y }; }
	Pii operator * (const ll& n) const { return { x * n, y * n }; }
	Pii operator / (const ll& n) const { return { x / n, y / n }; }
	ll operator * (const Pii& p) const { return { x * p.x + y * p.y }; }
	ll operator / (const Pii& p) const { return { x * p.y - y * p.x }; }
	ll Euc() const { return x * x + y * y; }
};
const Pii Oii = { 0, 0 };
typedef std::vector<Pii> Vpii;
Vpii star;
int get_min_dist_pos(const Vpii& P, const Pii& q) {
	ll d = INF;
	int k = -1;
	int sz = P.size();
	for (int i = 0; i < sz; i++) {
		if (d > (q - P[i]).Euc()) {
			d = (q - P[i]).Euc();
			k = i;
		}
	}
	return k;
}
struct Pos {
	ld x, y; int i;
	Pos(ld x_ = 0, ld y_ = 0, int i_ = 0) : x(x_), y(y_), i(i_) {}
	Pos operator + (const Pos& p) const { return { x + p.x, y + p.y }; }
	Pos operator - (const Pos& p) const { return { x - p.x, y - p.y }; }
	Pos operator * (const ld& n) const { return { x * n, y * n }; }
	Pos operator / (const ld& n) const { return { x / n, y / n }; }
	ld operator * (const Pos& p) const { return { x * p.x + y * p.y }; }
	ld operator / (const Pos& p) const { return { x * p.y - y * p.x }; }
	Pos operator ~ () const { return { -y, x }; }
	ld Euc() const { return x * x + y * y; }
	ld mag() const { return sqrt(Euc()); }
	Pos unit() const { return *this / mag(); }
	int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }
	friend bool cmpq(const Pos& a, const Pos& b) { return (a.quad() != b.quad()) ? a.quad() < b.quad() : sign(a / b) > 0; }
}; const Pos O = { 0, 0 };
typedef std::vector<Pos> Polygon;
Polygon pos;
ld cross(const Pos& d1, const Pos& d2, const Pos& d3) { return (d2 - d1) / (d3 - d2); }
Pos intersection(const Pos& p1, const Pos& p2, const Pos& q1, const Pos& q2) { ld a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2); return (p1 * a2 + p2 * a1) / (a1 + a2); }
struct Linear {//ps[0] -> ps[1] ::
	Pos ps[2];
	int i;
	Pos dir_;
	const Pos& operator [] (const int& i) const { return ps[i]; }
	const Pos& dir() const { return dir_; }
	Linear(Pos a = Pos(0, 0), Pos b = Pos(0, 0), int i_ = -1) {
		ps[0] = a;
		ps[1] = b;
		i = i_;
		//dir_ = (ps[1] - ps[0]).unit();
		dir_ = (ps[1] - ps[0]);
	}
	bool include(const Pos& p) const { return sign(dir_ / (p - ps[0])) > 0; }
	friend bool parallel(const Linear& l0, const Linear& l1) { return zero(l0.dir() / l1.dir()); }
	friend bool same_dir(const Linear& l0, const Linear& l1) { return parallel(l0, l1) && l0.dir() * l1.dir() > 0; }
	bool operator < (const Linear& l0) const {
		if (same_dir(*this, l0)) return l0.include(ps[0]);
		else return cmpq(this->dir(), l0.dir());
	}
};
typedef std::vector<Linear> VHP;
Pos intersection(const Linear& l1, const Linear& l2) { return intersection(l1[0], l1[1], l2[0], l2[1]); }
Linear bisector(const Pos& p, const Pos& q, const int& i) {
	Pos m = (p + q) * .5;
	Pos v = ~(q - p);
	return Linear(m, m + v, i);
}
Vint half_plane_intersection(std::vector<Linear>& HP) {
	auto check = [&](Linear& u, Linear& v, Linear& w) -> bool {
		return w.include(intersection(u, v));
		};
	std::sort(HP.begin(), HP.end());
	std::deque<Linear> dq;
	int sz = HP.size();
	for (int i = 0; i < sz; ++i) {
		if (i && same_dir(HP[i], HP[(i - 1) % sz])) continue;
		while (dq.size() > 1 && !check(dq[dq.size() - 2], dq[dq.size() - 1], HP[i])) dq.pop_back();
		while (dq.size() > 1 && !check(dq[1], dq[0], HP[i])) dq.pop_front();
		dq.push_back(HP[i]);
	}
	while (dq.size() > 2 && !check(dq[dq.size() - 2], dq[dq.size() - 1], dq[0])) dq.pop_back();
	while (dq.size() > 2 && !check(dq[1], dq[0], dq[dq.size() - 1])) dq.pop_front();
	sz = dq.size();
	if (sz < 3) return {};
	Vint HPI;
	for (int i = 0; i < sz; ++i) HPI.push_back(dq[i].i);
	return HPI;
}

int MST[1001], adj[1001][1001], depth[1001], parent[1001], B[1001], iB[1001];
ll weight[1001];
struct Edge { int v; ll w; };
struct Info {
	int i, p;
	ll c;
	Info(int i_ = 0, int p_ = -1, ll c_ = 0) : i(i_), p(p_), c(c_) {}
	bool operator < (const Info& x) const {
		if (c != x.c) return c < x.c;
		if (p != x.p) return B[p] < B[x.p];
		return i > x.i;
	}
};
std::vector<Edge> G[1001];
std::priority_queue<Info> PQ;

void change_parent(int u, int p, ll w) {
	int pre = parent[u];
	adj[u][pre] = adj[pre][u] = 0;

	parent[u] = p;
	adj[u][p] = adj[p][u] = 1;
	weight[u] = w;
	depth[u] = depth[p] + 1;

	std::queue<int> q;
	std::vector<int> visited(N, 0);
	q.push(u);
	visited[u] = 1;
	visited[p] = 1;
	while (q.size()) {
		int u = q.front(); q.pop();
		for (int v = 0; v < N; ++v) {
			if (v == u || !adj[u][v] || visited[v]) continue;
			depth[v] = depth[u] + 1;
			q.push(v);
			visited[v] = 1;
		}
	}
}

ll query(int u, int v) {
	ll ret = 0;
	if (depth[u] < depth[v]) std::swap(u, v);
	while (depth[u] != depth[v]) {
		ret = std::max(ret, weight[u]);
		u = parent[u];
	}
	while (u != v) {
		ret = std::max(ret, weight[u]);
		ret = std::max(ret, weight[v]);
		u = parent[u];
		v = parent[v];
	}
	return ret;
}

void prim() {
	int cur_star = 1;
	memset(MST, -1, sizeof MST);
	MST[0] = 1;
	B[0] = cur_star;
	iB[cur_star] = 0;
	for (const Edge& e : G[0]) {
		if (!~MST[e.v])
			PQ.push(Info(e.v, 0, e.w));
	}

	while (PQ.size()) {
		Info v = PQ.top(); PQ.pop();

		if (~MST[v.i]) continue;

		B[v.i] = ++cur_star;
		iB[cur_star] = v.i;
		MST[v.i] = 1;

		parent[v.i] = v.p;
		weight[v.i] = v.c * (star[v.i] - star[v.p]).Euc();
		adj[v.i][v.p] = adj[v.p][v.i] = 1;
		depth[v.i] = depth[v.p] + 1;

		// answer
		std::cout << v.i + 1 << ' ' << B[v.p] << ' ' << v.c << '\n';

		for (const Edge& e : G[v.i]) {
			if (!~MST[e.v])
				PQ.push(Info(e.v, v.i, e.w));
		}
	}
}

void solve() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cout.tie(0);
	std::cout << std::fixed;
	std::cout.precision(13);

	std::cin >> N >> Q1 >> Q2; Q = Q1 + Q2;
	star.resize(N); name.resize(N); pos.resize(N);
	for (int i = 0; i < N; i++) {
		std::cin >> star[i].x >> star[i].y >> name[i];
		star[i].i = i;
		pos[i] = { (ld)star[i].x, (ld)star[i].y };
	}
	preprocess(name);

	for (int i = 0; i < N; i++) {
		ld BND = 1e7;
		VHP hp = {
			Linear({ -BND, -BND }, { BND, -BND }),
			Linear({ BND, -BND }, { BND, BND }),
			Linear({ BND, BND }, { -BND, BND }),
			Linear({ -BND, BND }, { -BND, -BND })
		};
		for (int j = 0; j < N; j++) {
			if (i == j) continue;
			hp.push_back(bisector(pos[i], pos[j], j));
		}
		Vint res = half_plane_intersection(hp);
		for (const int& j : res) {
			//connect i, j
			if (j == -1) continue;
			G[i].push_back({ j, C(i, j) });
			G[j].push_back({ i, C(i, j) });
		}
	}

	prim();

	for (int q = 0; q < Q; ++q) {
		std::cin >> T;
		if (T == 1) {
			Pii s, e;
			std::cin >> s.x >> s.y >> e.x >> e.y;
			int si = get_min_dist_pos(star, s);
			int ei = get_min_dist_pos(star, e);
			std::cout << query(si, ei) << '\n';
		}
		else {
			int u, p;
			std::cin >> u >> p;
			u = iB[u];
			p = iB[p];
			change_parent(u, p, C(u, p) * (star[u] - star[p]).Euc());
		}
	}
}

int main() { solve(); return 0; }//boj18349 The Creation