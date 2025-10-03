#ifndef __KDT_MODULE_H__
#define __KDT_MODULE_H__

typedef long long ll;
const int LEN = 90'001;

struct Pii {
	int x, y, i;
	bool operator<(const Pii& o) const { return x == o.x ? y < o.y : x < o.x; }
	ll magnitude() const { return (ll)x * x + (ll)y * y; }
};

struct KDNode {
	Pii p;
	int sx, ex, sy, ey;
	KDNode* l;
	KDNode* r;
	bool spl() const;
	ll dist(const Pii& q) const;
	void dfs(const Pii& q, int& best_i, ll& best_d);
};

struct KDTree {
	KDNode tree[LEN << 1];
	void init(int s, int e, int i);
	int query(const Pii& q);
};

#endif