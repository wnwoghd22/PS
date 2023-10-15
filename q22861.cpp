#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <set>

const int LEN = 1001;

int folders;
std::unordered_map<std::string, int> folder_map;
std::set<std::string> children[LEN];
std::set<int> sub[LEN];
int par[LEN];
int size[LEN], cnt[LEN];

std::string get_token(const std::string& s) {
	if (s == "main") return s;
	int sep;
	for (sep = s.length() - 1; s[sep] != '/'; --sep);
	return s.substr(sep + 1);
}

int get_folder(const std::string& name) {
	if (folder_map.find(name) == folder_map.end())
		folder_map[name] = ++folders;
	return folder_map[name];
}

void dfs(int u) {
	size[u] = children[u].size();
	for (const int& v : sub[u]) {
		dfs(v);
		size[u] += size[v];
		for (const std::string& e : children[v]) {
			children[u].insert(e);
		}
	}
	cnt[u] = children[u].size();
}

int N, M, K, Q;
std::string sup, name;
int is_folder;

int main() {
	std::cin >> N >> M;
	for (int i = 0; i < N + M; ++i) {
		std::cin >> sup >> name >> is_folder;
		if (is_folder) {
			int p = get_folder(sup);
			int u = get_folder(name);
			sub[p].insert(u);
			par[u] = p;
		}
		else children[get_folder(sup)].insert(name);
	}

	std::cin >> K;
	for (int i = 0; i < K; ++i) { // O(K(N + M))
		std::cin >> name >> sup;
		int target = get_folder(get_token(sup));
		std::string token = get_token(name);
		if (folder_map.find(token) != folder_map.end()) { // is directory
			int u = folder_map[token];
			sub[par[u]].erase(u);
			for (const std::string& e : children[u]) {
				children[target].insert(e);
			}
			for (const int& v : sub[u]) {
				sub[target].insert(v);
				par[v] = target;
			}
		}
		else { // is file

		}
	}
	dfs(get_folder("main")); // O(NM)

	std::cin >> Q;
	while (Q--) {
		std::cin >> name;
		name = get_token(name);
		int i = get_folder(name);
		std::cout << cnt[i] << ' ' << size[i] << '\n';
	}
}