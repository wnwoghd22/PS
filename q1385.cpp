#include <iostream>
#include <stack>
#include <queue>

const int MAX = 1'000'001;

int len, base[MAX] = { 1, 2 };
int bs(int x) {
	int l = 0, r = len, m, ret = 0;
	while (l <= r) {
		m = l + r >> 1;
		if (base[m] > x) r = m - 1;
		else ret = std::max(m, ret), l = m + 1;
	}
	return ret;
}

bool visited[MAX];
int path[MAX];
int A, B, K;

std::queue<int> q;
std::stack<int> p;

int main() {
	for (len = 1; base[len] <= MAX; ++len)
		base[len + 1] = base[len] + len * 6;

	// for (int i = 0; i <= len; ++i) std::cout << i << ' ' << base[i] << '\n';

	std::cin >> A >> B;
	K = std::max(A, B);

	visited[A] = 1;

	q.push(A);

	while (q.size()) {
		int u = q.front(); q.pop();
		// std::cout << u << '\n';
		if (u == 1) {
			for (int v = 2; v <= std::min(K, 7); ++v) {
				if (!visited[v]) {
					visited[v] = path[v] = 1;
					q.push(v);
				}
			}
			continue;
		}
		int b = bs(u);
		// std::cout << "layer: " << b << '\n';
		int c = (u - base[b]) / b;
		int d = (u - 1) % b;
		int l = u == base[b] ? base[b + 1] - 1 : u - 1;
		if (l <= K && !visited[l]) {
			visited[l] = 1;
			path[l] = u;
			q.push(l);
		}
		int r = u == base[b + 1] - 1 ? base[b] : u + 1;
		if (r <= K && !visited[r]) {
			visited[r] = 1;
			path[r] = u;
			q.push(r);
		}
		// std::cout << "same layer: " << l << ' ' << r << '\n';
		if (d) { // on edge
			// std::cout << "edge\n";
			for (int i = 0, v; i <= 1; ++i) { // inner edge
				v = base[b - 1] + (b - 1) * c + d - 2 + i;
				if (v < base[b - 1]) v = base[b] - 1;
				// std::cout << "inner: " << v << '\n';
				if (!visited[v]) {
					visited[v] = 1;
					path[v] = u;
					q.push(v);
				}
			}
			for (int i = 0, v; i <= 1; ++i) { // outer edge
				v = base[b + 1] + (b + 1) * c + d - 1 + i;
				// std::cout << "outer: " << v << '\n';
				if (v <= K && !visited[v]) {
					visited[v] = 1;
					path[v] = u;
					q.push(v);
				}
			}
		}
		else { // corner
			// std::cout << "corner\n";
			int inner = base[b - 1] - 1 + (b - 1) * (c + 1);
			if (!inner) inner = 1;
			// std::cout << "inner: " << inner << '\n';
			if (!visited[inner]) {
				visited[inner] = 1;
				path[inner] = u;
				q.push(inner);
			}
			int outer = base[b + 1] - 1 + (b + 1) * (c + 1);
			if (outer <= K && !visited[outer]) {
				visited[outer] = 1;
				path[outer] = u;
				q.push(outer);
			}
			int l = outer - 1;
			if (l <= K && !visited[l]) {
				visited[l] = 1;
				path[l] = u;
				q.push(l);
			}
			int r = c == 5 ? base[b + 1] : outer + 1;
			if (r <= K && !visited[r]) {
				visited[r] = 1;
				path[r] = u;
				q.push(r);
			}
			// std::cout << "outer: " << l << ' ' << outer << ' ' << r << '\n';
		}
	}
	for (int v = B; v ^ A; v = path[v]) p.push(v);
	p.push(A);
	while (p.size()) std::cout << p.top() << ' ', p.pop();
}