#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

struct Vote { int idx, cat, dog; };
const int LEN = 501;
std::vector<int> a[LEN];
std::vector<Vote> cat;
std::vector<Vote> dog;
int d[LEN];
bool c[LEN];
int T, C, D, V;

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

void solve() {
	for (std::vector<int>& v : a) v.clear();
	cat.clear(); dog.clear();
	memset(c, 0, sizeof c);
	memset(d, 0, sizeof d);
	char pros, cons;
	int prosI, consI;
	std::cin >> C >> D >> V;
	for (int i = 1; i <= V; ++i) {
		std::cin >> pros >> prosI >> cons >> consI;
		if (pros == 'C') cat.push_back({ i, prosI, consI });
		if (pros == 'D') dog.push_back({ i, consI, prosI });
	}
	for (const Vote& cv : cat) {
		for (const Vote& dv : dog) {
			if (cv.cat == dv.cat || cv.dog == dv.dog) {
				a[cv.idx].push_back(dv.idx);
			}
		}
	}

	int count = 0;
	for (int i = 1; i <= V; ++i) {
		std::fill(c, c + V + 1, false);
		if (dfs(i)) ++count;
	}
	std::cout << V - count << '\n';
}

int main() {
	std::cin >> T;
	while (T--) solve();
}