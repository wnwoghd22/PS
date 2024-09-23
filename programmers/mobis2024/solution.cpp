#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;
const int LEN = 200'002;

std::vector<ll> p;

struct Node { ll a, d; } t[LEN << 2];
void update(int l, int r, int a, int d, int s = 0, int e = p.size() - 1, int i = 1) {
	if (r < p[s] || p[e] < l) return;
	if (l <= p[s] && p[e] <= r) {
		t[i].a += a;
		t[i].d += d;
		return;
	}
	int m = s + e >> 1;
	update(l, r, a, d, s, m, i << 1);
	update(l, r, a + (p[m + 1] - p[s]) * d, d, m + 1, e, i << 1 | 1);
}
ll get(ll x, int s = 0, int e = p.size() - 1, int i = 1) {
	if (x < p[s] || p[e] < x) return 0;
	if (s == e) return t[i].a;
	int m = s + e >> 1;
	return t[i].a + (p[x] - p[s]) * t[i].d + get(x, s, m, i << 1) + get(x, m + 1, e, i << 1 | 1);
}

int N, Q;
ll A[LEN], X[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> Q;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	for (int i = 0; i < Q; ++i) {
		std::cin >> X[i];
		p.push_back(X[i]);
	}
	std::sort(p.begin(), p.end());
	p.erase(std::unique(p.begin(), p.end()), p.end());
	A[N + 1] = 1e15;
	for (int i = 3; i <= N + 1; ++i) {
		ll a = A[i - 2] - A[i - 3] - 1;
		ll b = A[i - 1] - A[i - 2] + 1;
		ll c = A[i] - A[i - 1] - 1;
		if (a < c) std::swap(a, c);
		update(b, b + c, 1, 1); 
		update(b + c + 1, b + a, c, 0);
		update(a + b + 1, a + b + c, c - 1, -1);
	}
	for (int i = 0; i < Q; ++i)
		std::cout << get(X[i]) << '\n';
}