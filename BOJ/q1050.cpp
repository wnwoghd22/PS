#include <iostream>
#include <vector>
#include <map>

typedef long long ll;
const ll INF = 1e9 + 1;

struct E { int a, x; };

int y[50];
std::vector<E> eq[50];

int N, M, cnt;
char expr[51];

std::map<std::string, int> idx;
std::map<int, ll> map;
std::string name;

int main() {
	std::cin >> N >> M;
	for (int i = 0, c; i < N; ++i) {
		std::cin >> name >> c;
		if (idx.find(name) == idx.end()) idx[name] = cnt++;
		map[idx[name]] = c;
	}
	for (int i = 0, a = -1; i < M; ++i) {
		std::string name;
		std::cin >> expr;
		for (int j = 0; 1; ++j) {
			if (expr[j] == '+' || expr[j] == 0) {
				if (idx.find(name) == idx.end()) idx[name] = cnt++;
				eq[i].push_back({ a, idx[name] });
				name = "";
				if (!expr[j]) break;

			}
			else if (expr[j] == '=') {
				if (idx.find(name) == idx.end()) idx[name] = cnt++;
				y[i] = idx[name];
				name = "";
			}
			else if (expr[j] >= '0' && expr[j] <= '9') a = expr[j] - '0';
			else name += expr[j];
		}
	}
	for (int k = 0; k < M; ++k) {
		for (int i = 0; i < M; ++i) {
			const std::vector<E>& cur = eq[i];
			ll cost = 0;
			for (const E& e : cur) {
				if (map.find(e.x) == map.end()) {
					cost = -1;
					break;
				}
				cost += e.a * map[e.x];
				if (cost >= INF) cost = INF;
			}
			if (cost < 0) continue;
			if (map.find(y[i]) == map.end()) map[y[i]] = cost;
			else map[y[i]] = std::min(map[y[i]], cost);
		}
	}
	ll ret;
	if (idx.find("LOVE") == idx.end() || map.find(idx["LOVE"]) == map.end()) ret = -1;
	else ret = map[idx["LOVE"]];
	if (ret >= INF) ret = INF;
	std::cout << ret;
}