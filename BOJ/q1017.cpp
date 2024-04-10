#include <iostream>
#include <vector>
#include <algorithm>

const int LEN = 51;
const int MAX = 2001;

std::vector<int> a[LEN];
std::vector<int> v[2];
int l[LEN], d[LEN];
bool c[LEN], p[MAX];
int N;

bool dfs(int x, const int fixed) {
	for (const int& t : a[x]) {
		if (t == fixed) continue;
		if (c[t]) continue;
		c[t] = true;
		if (!d[t] || dfs(d[t], fixed)) {
			d[t] = x;
			return true;
		}
	}
	return false;
}

int main() {
	for (int i = 2; i * i < MAX; ++i)
		if (!p[i]) for (int j = i * 2; j < MAX; j += i) p[j] = true;
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> l[i];
	for (int i = 0; i < N; ++i) v[(l[i] ^ l[0]) & 1].push_back(l[i]);

	if (v[0].size() != v[1].size()) {
		std::cout << -1;
		return 0;
	}
	for (int i = 0; i < N >> 1; ++i)
		for (int j = 0; j < N >> 1; ++j)
			if (!p[v[0][i] + v[1][j]]) a[i + 1].push_back(j + 1);

	std::vector<int> result;
	for (const int& e : a[1]) {
		std::fill(d, d + LEN, 0);
		int count = 1;
		for (int i = 2; i <= N >> 1; ++i) {
			std::fill(c, c + LEN, false);
			if (dfs(i, e)) ++count;
		}
		if (count == N >> 1) result.push_back(v[1][e - 1]);
	}
	if (!result.size()) std::cout << -1;
	else {
		std::sort(result.begin(), result.end());
		for (const int& e : result) std::cout << e << ' ';
	}
}