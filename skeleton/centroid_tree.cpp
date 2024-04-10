#include <iostream>
#include <vector>

const int LEN = 100'001;
std::vector<int> tree[LEN];
std::vector<int> cent_tree[LEN];

int size[LEN];
bool visited[LEN];

void addEdge(int u, int v) {
	tree[u].push_back(v);
	tree[v].push_back(u);
}

int get_size(int u, int p = 0) {
	size[u] = 1;
	for (const int& v : tree[u]) {
		if (v == p || visited[v]) continue;
		size[u] += get_size(v, u);
	}
	return size[u];
}

int get_cent(int u, int p, int s) {
	for (const int& v : tree[u]) {
		if (v != p && !visited[v] && size[v] * 2 > s)
			return get_cent(v, u, s);
	}
	return u;
}

int decompose_tree(int u) {
	int cent = get_cent(u, 0, get_size(u));
	std::cout << u << ' ' << size[u] << ' ' << cent << '\n';
	visited[cent] = 1;
	for (const int& v : tree[cent]) {
		if (!visited[v]) {
			int sub_cent = decompose_tree(v);
			cent_tree[cent].push_back(sub_cent);
			cent_tree[sub_cent].push_back(cent);
		}
	}
	return cent;
}

int main() {
	addEdge(1, 4);
	addEdge(2, 4);
	addEdge(3, 4);
	addEdge(4, 5);
	addEdge(5, 6);
	addEdge(6, 7);
	addEdge(7, 8);
	addEdge(7, 9);
	addEdge(6, 10);
	addEdge(10, 11);
	addEdge(11, 12);
	addEdge(11, 13);
	addEdge(12, 14);
	addEdge(13, 15);
	addEdge(13, 16);

	decompose_tree(1);
}