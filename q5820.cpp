#include <iostream>
#include <vector>
#include <map>

const int INF = 1e9;
const int LEN = 200'000;
struct Edge { int v, w; };
std::vector<Edge> graph[LEN];
int N, K, size[LEN], visited[LEN];
std::map<int, int> min_dep;
std::vector<Edge> cur_dep;

int get_size(int u, int p = -1) {
	size[u] = 1;
	for (const Edge& e : graph[u]) {
		if (e.v != p && !visited[e.v])
			size[u] += get_size(e.v, u);
	}
	return size[u];
}

int get_cent(int u, int p, int s) {
	for (const Edge& e : graph[u]) {
		if (e.v != p && !visited[e.v] && size[e.v] * 2 > s)
			return get_cent(e.v, u, s);
	}
	return u;
}

int get_path(int u, int p, int depth, int length) {
	if (length == depth) return depth;
	if (length > depth) return INF;
	int result = INF;
	if (min_dep.find(K - length) != min_dep.end())
		result = std::min(result, min_dep[K - length] + depth);
	cur_dep.push_back({ length, depth });
	for (const Edge& e : graph[u]) {
		if (e.v != p && !visited[e.v])
			result = std::min(result, get_path(e.v, u, depth + 1, length + e.w));
	}
	return result;
}

int f(int u) {
	int result = INF;
	int cent = get_cent(u, -1, get_size(u));

}

int best_path(int N, int K, int H[][2], int L[]) {

}