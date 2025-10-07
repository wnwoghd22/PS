#include "kdt_module.h"

#include <algorithm>

ll KDNode::dist(const Pii& q) const {
	ll dx = 0, dy = 0;
	if (q.x < sx) dx = sx - q.x;
	else if (q.x > ex) dx = q.x - ex;
	if (q.y < sy) dy = sy - q.y;
	else if (q.y > ey) dy = q.y - ey;
	return dx * dx + dy * dy;
}

bool KDNode::spl() const { return ex - sx < ey - sy; }
void KDNode::dfs(const Pii& q, int& best_i, ll& best_d) {
	if (dist(q) >= best_d) return;
	ll d = (p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y);
	if (d < best_d) { best_i = p.i; best_d = d; }
	KDNode* l = this->l;
	KDNode* r = this->r;
	if (spl() && q.y >= p.y) std::swap(l, r);
	if (!spl() && q.x >= p.x) std::swap(l, r);
	if (l) l->dfs(q, best_i, best_d);
	if (r) r->dfs(q, best_i, best_d);
}

KDNode* KDTree::init(int s, int e, int i) {
	if (s > e) return 0;
	tree[i].sx = 1e9; tree[i].ex = -1e9; 
	tree[i].sy = 1e9; tree[i].ey = -1e9;
	int m = s + e >> 1;
	for (int k = s; k <= e; ++k) {
		tree[i].ex = std::max(tree[k].ex, pos[k].x);
		tree[i].ey = std::max(tree[k].ey, pos[k].y);
		tree[i].sx = std::min(tree[k].sx, pos[k].x);
		tree[i].sy = std::min(tree[k].sy, pos[k].y);
	}

	std::sort(pos + s, pos + e + 1, tree[i].spl() ? 
		[](const Pii& p, const Pii& q) { return p.y == q.y ? p.x < q.x : p.y < q.y; } : 
		[](const Pii& p, const Pii& q) { return p.x == q.x ? p.y < q.y : p.x < q.x; });
	tree[i].p = pos[m];

	tree[i].l = init(s, m - 1, i << 1);
	tree[i].r = init(m + 1, e, i << 1 | 1);

	return &tree[i];
}

int KDTree::query(const Pii& q) {
	int i = -1; ll d = 1e17;
	tree[1].dfs(q, i, d);
	return i;
}