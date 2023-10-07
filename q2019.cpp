#include <iostream>
#include <vector>
#include <map>

const int LEN = 121;
typedef long long ll;

struct Pos {
	ll x, y;
	bool operator<(const Pos& r) const { return x == r.x ? y < r.y : x < r.x; }
	bool operator==(const Pos& r) const { return x == r.x && y == r.y; }
};
ll cross(const Pos& p1, const Pos& p2, const Pos& p3, const Pos& p4) { return (p2.x - p1.x) * (p4.y - p3.y) - (p2.y - p1.y) * (p4.x - p3.x); }
ll dot(const Pos& p1, const Pos& p2, const Pos& p3, const Pos& p4) { return (p2.x - p1.x) * (p4.x - p3.x) + (p2.y - p1.y) * (p4.y - p3.y); }
bool intersect(const Pos& p1, const Pos& p2, const Pos& p3, const Pos& p4) {
	bool f11 = cross(p1, p2, p2, p3) * cross(p2, p1, p1, p4) > 0;
	bool f12 = cross(p3, p4, p4, p1) * cross(p4, p3, p3, p2) > 0;
	bool line = !cross(p1, p3, p3, p2) && dot(p1, p3, p3, p2) >= 0 ||
		!cross(p1, p4, p4, p2) && dot(p1, p4, p4, p2) >= 0 ||
		!cross(p3, p1, p1, p4) && dot(p3, p1, p1, p4) >= 0 ||
		!cross(p3, p2, p2, p4) && dot(p3, p2, p2, p4) >= 0;
	return f11 && f12 || line;
}

std::map<Pos, int> vert;
std::map<int, Pos> pos;
int ord = 1;
int get(int x, int y) {
	Pos p = { x, y };
	if (vert.find(p) != vert.end()) return vert[p];
	pos[ord] = p;
	vert[p] = ord;
	std::cout << "push " << ord << ' ' << x << ", " << y << '\n';
	return ord++;
}

struct Edge { Pos a, b; };
bool intersect(const Edge& r, const Edge& l) { return intersect(r.a, r.b, l.a, l.b); }

int N;

std::vector<int> graph[LEN];
int visited[LEN];

int size;

std::vector<Edge> edges;
bool dfs(int u, int p = 0) {
	++size;
	visited[u] = visited[p] + 1;
	bool result = graph[u].size() == 2;
	for (const int& v : graph[u]) {
		if (v == p) continue;
		
		if (!visited[v]) {
			std::cout << u << " -> " << v << '\n';
			edges.push_back({ pos[u], pos[v] });
			result &= dfs(v, u);
		}
		else if (visited[v] < visited[u]) {
			std::cout << u << " -> " << v << '\n';
			edges.push_back({ pos[u], pos[v] });
		}
	}
	return result;
}

bool f(int i) {
	size = 0;
	edges.clear();
	std::cout << "----------------------\n";
	
	bool result = dfs(i);
	for (const Edge& e : edges) {
		std::cout << e.a.x << ' ' << e.a.y << ' ' << e.b.x << ' ' << e.b.y << '\n';
	}
	if (!result) return false;
	if (size < 3) return false;

	for (int l = 0; l < edges.size(); ++l) {
		for (int k = 2; k < edges.size() - 3; ++k) {
			if (intersect(edges[l], edges[(l + k) % edges.size()]))
				return false;
		}
	}

	return true;
}

int main() {
	std::cin >> N;
	for (int i = 0, x1, y1, x2, y2, u, v; i < N; ++i) {
		std::cin >> x1 >> y1 >> x2 >> y2;
		u = get(x1, y1); v = get(x2, y2);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	int result = 0;
	for (int u = 1; u < ord; ++u)
		if (!visited[u] && f(u)) ++result;
	std::cout << result;
}