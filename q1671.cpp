#include <iostream>
#include <vector>
#include <algorithm>

const int LEN = 51;

struct Shark {
	int a, b, c;
	bool operator==(const Shark& l) const { return a == l.a && b == l.b && c == l.c; }
	bool operator>=(const Shark& l) const { return a >= l.a && b >= l.b && c >= l.c; }
};

std::vector<int> a[LEN];
Shark l[LEN];
int d[LEN];
bool c[LEN];
int N;

bool dfs(int x) {
	for (const int& t : a[x]) {
		if (c[t]) continue;
		c[t] = true;
		if (!d[t] || dfs(d[t])) {
			d[t] = x;
			return true;
		}
	}
	return false;
}

int main() {
	std::cin >> N;
	for (int a, b, c, i = 1; i <= N; ++i) {
		std::cin >> a >> b >> c;
		l[i] = { a, b, c };
	}

	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			if (i != j && l[i] >= l[j] && !(l[i] == l[j] && i < j))
				a[i].push_back(j);
	
	int count = 0;
	for (int i = 0; i < N * 2; ++i) {
		std::fill(c, c + LEN, false);
		if (dfs(i / 2 + 1)) ++count;
	}
	std::cout << N - count;
}