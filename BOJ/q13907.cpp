#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>

typedef long long int ll;
typedef long double ld;
const ll INF = 1e17;
const int V_LEN = 1'001;
const int E_LEN = 30'000;

ll dp[V_LEN][V_LEN], x, p;
int N, M, K, S, D, a, b, w;
struct Edge { int v, w; };
std::vector<Edge> graph[V_LEN];
struct Info { 
	ll u, d, c; 
	bool operator<(const Info& r) const { return d > r.d; }
};

void dijkstra(int s) {
	std::priority_queue<Info> q;
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			dp[i][j] = INF;

	dp[s][0] = 0;
	q.push({ s, 0, 0 });
	while (q.size()) {
		Info i = q.top(); q.pop();
		if (dp[i.u][i.c] < i.d) continue;
		for (const Edge& e : graph[i.u]) {
			if (dp[i.u][i.c] + e.w < dp[e.v][i.c + 1]) {
				dp[e.v][i.c + 1] = dp[i.u][i.c] + e.w;
				q.push({ e.v, dp[e.v][i.c + 1], i.c + 1 });
			}
		}
	}
}

struct Line {
	ll a, b;
	ld x;
	bool operator<(const Line& r) { return a == r.a ? b < r.b : a > r.a; }
	ld operator&(const Line& r) const { return (ld)(r.b - b) / (a - r.a); }
	ll f(ll x) { return a * x + b; }
};
std::vector<Line> lines;
std::vector<Line> hull;
void add_line(Line l) {
	if (hull.empty()) {
		hull.push_back(l);
		return;
	}
	if (hull.back().a == l.a) return;
	while (hull.size() > 1) {
		if (hull.back().x > (hull.back() & l)) hull.pop_back();
		else break;
	}
	l.x = hull.back() & l;
	hull.push_back(l);
}
int ptr = 0;
ll f(ll x) {
	while (ptr < hull.size() - 1 && x >= hull[ptr + 1].x) ++ptr;
	return hull[ptr].f(x);
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> M >> K >> S >> D;
	while (M--) {
		std::cin >> a >> b >> w;
		graph[a].push_back({ b, w });
		graph[b].push_back({ a, w });
	}
	dijkstra(S);
	for (int i = 1; i <= N; ++i) {
		if (dp[D][i] != INF)
			lines.push_back({ i, dp[D][i], -INF });
	}
	std::sort(lines.begin(), lines.end());
	for (const Line& l : lines) add_line(l);

	std::cout << f(0) << '\n';
	while (K--) {
		std::cin >> p;
		std::cout << f(x += p) << '\n';
	}
}