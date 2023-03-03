#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

typedef long long int ll;
struct Edge { ll v, p, q; };
std::vector<Edge> graph[10];

ll N, P[10], Q[10], R[10];
ll gcd(ll a, ll b) { return !b ? a : gcd(b, a % b); }
void dfs(int u, ll p, ll q) {
	P[u] = p, Q[u] = q;
	for (const Edge& e : graph[u]) {
		if (!P[e.v])
			dfs(e.v, p * e.p, q * e.q);
	}
}

int main() {
	// freopen("input.txt", "r", stdin);

	std::cin >> N;
	for (int i = 0, a, b, p, q; i < N - 1; ++i) {
		std::cin >> a >> b >> p >> q;
		ll g = gcd(p, q);
		p /= g, q /= g;
		graph[a].push_back({ b, p, q });
		graph[b].push_back({ a, q, p });
	}
	dfs(0, 1, 1);

	// for (int i = 0; i < N; ++i) std::cout << P[i] << ' ' << Q[i] << '\n';

	R[0] = 1;
	for (int i = 1; i < N; ++i) {
		R[i] = R[0] * Q[i];
		for (int j = 0; j < i; ++j)
			R[j] *= P[i];
		ll g = R[0];
		for (int j = 1; j <= i; ++j) g = gcd(g, R[j]);
		for (int j = 0; j <= i; ++j) R[j] /= g;
	}
	for (int i = 0; i < N; ++i) std::cout << R[i] << ' ';
}