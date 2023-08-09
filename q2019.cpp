#include <iostream>
#include <vector>
#include <map>

const int LEN = 121;
struct Pos {
	int x, y;
	bool operator<(const Pos& r) const { return x == r.x ? y < r.y : x < r.x; }
	bool operator==(const Pos& r) const { return x == r.x && y == r.y; }
};
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
bool intersect(const Edge& r, const Edge& l) {
	if (r.a == l.a || r.a == l.b || r.b == l.a || r.b == l.b) return false;



	return false;
}

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
		for (int r = l + 1; r < edges.size(); ++r) {
			if (intersect(edges[l], edges[r]))
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