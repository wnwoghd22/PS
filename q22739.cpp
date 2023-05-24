#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <map>

std::map<std::string, int> lang_map;
std::string ls[30];
std::string s;

int N, M, K;
int students[20];
int p[21];
int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
int join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return 1;
}

int check(int langs) { // O(M^2 log M)
	memset(p, -1, sizeof p);
	for (int i = 0; i < M; ++i)
		for (int j = i + 1; j < M; ++j)
			if (students[i] & students[j] & langs)
				join(i, j);
	return p[find(0)] == -M;
}

int min, bit;

void dfs(int d, int i, int b) { // O(N C 5)
	if (d == min) return;

	if (check(b)) {
		if (d < min) {
			bit = b;
			min = d;
		}
	}

	for (int j = i; j < M; ++j)
		dfs(d + 1, j + 1, b | 1 << j);
}

int solve() {
	std::cin >> N >> M;
	if (!N && !M) return 0;

	min = 6; bit = 0;
	lang_map.clear();
	for (int i = 0; i < N; ++i) {
		std::cin >> ls[i];
		lang_map[ls[i]] = i;
	}
	for (int i = 0; i < M; ++i) {
		students[i] = 0;
		std::cin >> K;
		while (K--) {
			std::cin >> s;
			students[i] |= 1 << lang_map[s];
		}
	}
	dfs(0, 0, 0);

	if (!bit) std::cout << "Impossible\n";
	else {
		std::cout << min << '\n';
		for (int i = 0; i < M; ++i) {
			if (bit & 1 << i)
				std::cout << ls[i] << '\n';
		}
	}
	std::cout << '\n';
	
	return 1;
}

int main() { freopen("input.txt", "r", stdin); while (solve()); }