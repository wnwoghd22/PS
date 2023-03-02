#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

const int INF = 1e9;
const int LEN = 200'000;
struct Edge { int v, w; };
std::vector<Edge> graph[LEN];
int n, k, size[LEN], visited[LEN];
std::map<int, int> min_dep;
std::vector<Edge> cur_dep;
void merge() {
	for (const Edge& e : cur_dep) {
		if (min_dep.find(e.v) == min_dep.end()) min_dep[e.v] = e.w;
		else min_dep[e.v] = std::min(min_dep[e.v], e.w);
	}
	cur_dep.clear();
}

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
	if (length == k) return depth;
	if (length > k) return INF;
	int result = INF;
	if (min_dep.find(k - length) != min_dep.end())
		result = std::min(result, min_dep[k - length] + depth);
	cur_dep.push_back({ length, depth });
	for (const Edge& e : graph[u]) {
		if (e.v != p && !visited[e.v])
			result = std::min(result, get_path(e.v, u, depth + 1, length + e.w));
	}
	return result;
}

int f(int u) {
	min_dep.clear();
	int result = INF;
	int cent = get_cent(u, -1, get_size(u));
	// std::cout << "centroid: " << cent << '\n';
	visited[cent] = true;
	for (const Edge& e : graph[cent]) {
		if (!visited[e.v])
			result = std::min(result, get_path(e.v, u, 1, e.w));
		merge();
	}
	for (const Edge& e : graph[cent]) {
		if (!visited[e.v])
			result = std::min(result, f(e.v));
	}
	return result;
}

int best_path(int N, int K, int H[][2], int L[]) {
	n = N, k = K;
	for (int i = 0; i < N - 1; ++i) {
		int u = H[i][0], v = H[i][1], w = L[i];
		graph[u].push_back({ v, w });
		graph[v].push_back({ u, w });
	}
	int result = f(0);
	return result != INF ? result : -1;
}

int N, K, H[LEN][2], L[LEN];
int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> K;
	for (int i = 0; i < N - 1; ++i) {
		std::cin >> H[i][0] >> H[i][1] >> L[i];
	}
	std::cout << best_path(N, K, H, L);
}