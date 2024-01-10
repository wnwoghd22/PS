#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

typedef long long ll;
const int INF = 1e9 + 7;
const int LEN = 250'001;

struct Arc {
	int s, e, i;
	bool operator<(const Arc& r) const {
		return s == r.s ? e > r.e : s < r.s;
	}
} arcs[LEN];

std::vector<Arc> stack;

std::vector<int> graph[LEN];
int w[LEN];

std::priority_queue<ll> merged;
std::priority_queue<ll> pq[LEN];
int q_idx[LEN];

void dfs(int u) {
	int l = q_idx[u] = u, r;
	for (const int& v : graph[u]) {
		dfs(v);
		r = q_idx[v];
		while (pq[l].size() && pq[r].size()) {
			ll m = pq[l].top() + pq[r].top();
			pq[l].pop(); pq[r].pop();
			merged.push(m);
		}
		l = pq[l].size() ? l : r;
		while (merged.size()) {
			pq[l].push(merged.top());
			merged.pop();
		}
	}
	q_idx[u] = l;
	pq[l].push(w[u]);
}
int N;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	arcs[0] = { -INF, INF, 0 };
	for (int i = 1; i <= N; ++i) {
		std::cin >> arcs[i].s >> arcs[i].e >> w[i];
		arcs[i].i = i;
	}
	std::sort(arcs, arcs + N + 1);
	stack.push_back(arcs[0]);
	for (int i = 1; i <= N; ++i) {
		while (stack.back().e <= arcs[i].s) stack.pop_back();
		graph[stack.back().i].push_back(arcs[i].i);
		stack.push_back(arcs[i]);
	}
	dfs(0);
	ll ret = 0;
	int idx = q_idx[0];
	for (int i = 0; i < N; ++i) {
		if (pq[idx].size()) {
			ret += pq[idx].top();
			pq[idx].pop();
		}
		std::cout << ret << ' ';
	}
}