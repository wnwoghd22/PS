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

void KDTree::init(int s, int e, int i) {
	
}

int KDTree::query(const Pii& q) {
	int i = -1; ll d = 1e17;
	tree[1].dfs(q, i, d);
	return i;
}