#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

const int INF = 1e9 + 7;
const int LEN = 101;
int N, d, d2;

struct Pos { int x, y; } pos[LEN];
int dist(const Pos& p1, const Pos& p2) {
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
int cross(const Pos& p1, const Pos& p2, const Pos& p3) {
	int mul = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p3.x * p2.y - p2.x * p1.y - p1.x * p3.y;
	if (mul) mul /= std::abs(mul);
	return mul;
}
std::vector<int> vert_u, vert_v;

int u_len, v_len;
int U[LEN]; // pair of u(left side) u->v. 0 if u does not have any pair
int V[LEN]; // pair of v(right side) v->u. 0 if v does not have any pair
int D[LEN]; // distance of left side vertices
std::vector<int> graph[LEN];

bool bfs() {
	std::queue<int> q;
	for (const int& u : vert_u) {
		if (!U[u]) { // free vertex
			D[u] = 0;
			q.push(u);
		}
		else D[u] = INF;
	}
	D[0] = INF;

	while (q.size()) {
		int u = q.front(); q.pop();

		if (D[u] < D[0]) {
			for (const int& v : graph[u]) {
				if (D[V[v]] == INF) { // v is not considered so far
					D[V[v]] = D[u] + 1;
					q.push(V[v]);
				}
			}
		}
	}
	return D[0] != INF; // if could come back to NIL using alternating path then there is an augmenting path
}

bool dfs(int u) {
	if (u) {
		for (const int& v : graph[u]) {
			if (D[V[v]] == D[u] + 1) {
				if (dfs(V[v])) {
					V[v] = u;
					U[u] = v;
					return true;
				}
			}
		}
		D[u] = INF;
		return false;
	}
	return true;
}

int hopcroft_karp() {
	memset(U, 0, sizeof U);
	memset(V, 0, sizeof V);
	int result = 0;

	while (bfs()) {
		for (const int& u : vert_u)
			if (!U[u] && dfs(u))
				++result;
	}
	return result;
}

bool visited[LEN], result[LEN];
void dfs_mask(int u) {
	visited[u] = true;
	for (const int& v : graph[u]) {
		if (U[u] == v || visited[v]) continue;
		visited[v] = true;
		dfs_mask(V[v]);
	}
}

int _u, _v, m;

int check(int u, int v) {
	int count = 2, r = dist(pos[u], pos[v]);
	vert_u.clear();
	vert_v.clear();
	for (std::vector<int>& v : graph) v.clear();
	for (int i = 1; i <= N; ++i) {
		if (i == u || i == v) continue;
		if (dist(pos[u], pos[i]) <= r && dist(pos[v], pos[i]) <= r) {
			++count;
			int side = cross(pos[u], pos[v], pos[i]);
			// std::cout << u << ' ' << v << ' ' << i << ' ' << side << '\n';
			if (side < 0) vert_u.push_back(i);
			if (side > 0) vert_v.push_back(i);
		}
	}
	u_len = vert_u.size();
	v_len = vert_v.size();
	for (const int& i : vert_u)
		for (const int& j : vert_v)
			if (dist(pos[i], pos[j]) > r)
				graph[i].push_back(j);

	return count - hopcroft_karp();
}

int main() {
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> d;
	d2 = d * d;

	for (int i = 1; i <= N; ++i) std::cin >> pos[i].x >> pos[i].y;
	for (int i = 1; i < N; ++i) {
		for (int j = i + 1; j <= N; ++j) {
			if (dist(pos[i], pos[j]) <= d2) {
				int c = check(i, j);
				if (c > m) {
					m = c;
					_u = i, _v = j;
				}
			}
		}
	}
	if (!m) std::cout << "1\n1";
	else if (m) {
		std::cout << m << '\n';
		vert_u.clear();
		vert_v.clear();
		result[_u] = result[_v] = true;
		int r = dist(pos[_u], pos[_v]);
		for (std::vector<int>& v : graph) v.clear();
		for (int i = 1; i <= N; ++i) {
			if (i == _u || i == _v) continue;
			if (dist(pos[_u], pos[i]) <= r && dist(pos[_v], pos[i]) <= r) {
				result[i] = true;
				int side = cross(pos[_u], pos[_v], pos[i]);
				// std::cout << u << ' ' << v << ' ' << i << ' ' << side << '\n';
				if (side < 0) vert_u.push_back(i);
				if (side > 0) vert_v.push_back(i);
			}
		}
		u_len = vert_u.size();
		v_len = vert_v.size();
		for (const int& i : vert_u)
			for (const int& j : vert_v)
				if (dist(pos[i], pos[j]) > r)
					result[i] = result[j] = false,
					graph[i].push_back(j);

		hopcroft_karp();

		for (const int& u : vert_u) {
			if (!U[u])
				dfs_mask(u);
		}
		for (const int& u : vert_u) {
			if (visited[u])
				result[u] = true;
		}
		for (const int& v : vert_v) {
			if (!visited[v])
				result[v] = true;
		}

		for (int i = 1; i <= N; ++i)
			if (result[i])
				std::cout << i << ' ';
	}
}