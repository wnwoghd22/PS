#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

typedef long long int ll;
const int LEN = 5001;

struct Node { // node for union-find
	int p;
	ll area;
	ll l, r, d, u;
	Node() : p(-1), area(0), l(0), r(0), d(0), u(0) {}
	Node(int i, Node n) : p(i), area(n.area), l(n.l), r(n.r), u(n.u), d(n.d) {}
	ll get_defect() { return (r - l) * (u - d) - area; }
} p[LEN];

struct Rect {
	ll l, r, d, u;
	ll get_area() { return (r - l) * (u - d); }
	bool operator&(const Rect& rhs) const { // check adj
		return (std::max(l, rhs.l) < std::min(r, rhs.r) && (u == rhs.d || d == rhs.u)) ||
			(std::max(d, rhs.d) < std::min(u, rhs.u) && (l == rhs.r || r == rhs.l));
	}
} A[LEN];

Node find(int i) {
	if (p[i].p < 0) return Node(i, p[i]);
	return p[i] = find(p[i].p);
}

bool join(int a, int b) {
	a = find(a).p, b = find(b).p;
	if (a == b) return false;
	if (p[a].p < p[b].p) { // merge b to a
		p[a].area += p[b].area;
		p[a].l = std::min(p[a].l, p[b].l);
		p[a].r = std::max(p[a].r, p[b].r);
		p[a].d = std::min(p[a].d, p[b].d);
		p[a].u = std::max(p[a].u, p[b].u);
		p[a].p += p[b].p;
		p[b].p = a;
	}
	else {
		p[b].area += p[a].area;
		p[b].l = std::min(p[b].l, p[a].l);
		p[b].r = std::max(p[b].r, p[a].r);
		p[b].d = std::min(p[b].d, p[a].d);
		p[b].u = std::max(p[b].u, p[a].u);
		p[b].p += p[a].p;
		p[a].p = b;
	}
	return true;
}

std::vector<int> graph[LEN];
int N, visited[LEN];
bool cut[LEN];

int dfs(int u, int p = 0, bool root = true) {
	int min = visited[u] = visited[p] + 1, child = 0;
	for (const int& v : graph[u]) {
		if (visited[v]) min = std::min(min, visited[v]);
		else {
			++child;
			int next = dfs(v, u, false);
			if (!root) cut[u] = next >= visited[u];
			min = std::min(min, next);
		}
	}
	if (root) cut[u] = child >= 2;
	return min;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (ll i = 1, l, r, d, u; i <= N; ++i) {
		std::cin >> l >> r >> d >> u;
		p[i].l = A[i].l = l;
		p[i].r = A[i].r = r;
		p[i].d = A[i].d = d;
		p[i].u = A[i].u = u;
		p[i].area = A[i].get_area();
	}
	for (int i = 1; i < N; ++i) {
		for (int j = i + 1; j <= N; ++j) {
			if (A[i] & A[j]) {
				graph[i].push_back(j);
				graph[j].push_back(i);
				join(i, j);
			}
		}
	}
	for (int i = 1; i <= N; ++i) {
		if (!visited[i])
			dfs(i);
	}
	ll max_defect = 0;
	ll min_area = 1e17;
	int result = -1;
	for (int i = 1; i <= N; ++i) {
		if (cut[i]) continue;
		ll cur_defect = find(i).get_defect();
		if (cur_defect > max_defect) {
			max_defect = cur_defect;
			min_area = A[i].get_area();
			result = i;
		}
		else if (cur_defect == max_defect) {
			ll cur_area = A[i].get_area();
			if (cur_area < min_area) {
				min_area = cur_area;
				result = i;
			}
		}
	}
	std::cout << result;
}