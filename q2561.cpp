#include <iostream>

struct P { 
	int l, r;
	int s() { return abs(r - l) + 1; }
} p[8];
int N, C, A[1000], depth, ans[3][2];

bool check() {
	for (int i = 0; i < C; ++i)
		if (abs(p[i].r - p[i + 1].l) != 1)
			return false;
	return true;
}

void flip(int l, int r) {
	while (l <= r) {
		P tmp = { p[l].r, p[l].l };
		p[l] = { p[r].r, p[r].l };
		p[r] = tmp;
		++l;
		--r;
	}
}

bool dfs(int d) {
	if (check()) {
		depth = d - 1;
		return true;
	}
	if (d == 3) return false;
	ans[d][0] = 1;
	for (int i = 0; i <= C; ans[d][0] += p[i++].s()) {
		ans[d][1] = ans[d][0] - 1;
		for (int j = i; j <= C; ++j) {
			ans[d][1] += p[j].s();
			flip(i, j);
			if (dfs(d + 1))
				return true;
			flip(i, j);
		}
	}
	return false;
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	p[C].l = p[C].r = A[0];
	for (int i = 1; i < N; ++i) {
		if (abs(A[i] - A[i - 1]) != 1) {
			++C;
			p[C].l = p[C].r = A[i];
		}
		else p[C].r = A[i];
	}
	std::cout << C << '\n';
	for (int i = 0; i <= C; ++i) std::cout << p[i].l << ' ' << p[i].r << '\n';
	dfs(0);
	for (int i = 0; i < 3; ++i) {
		if (i > depth) std::cout << "1 1\n";
		else std::cout << ans[i][0] << ' ' << ans[i][1] << '\n';
	}
}