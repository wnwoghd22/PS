#include <iostream>
#include <algorithm>

typedef long long ll;
const ll INF = 1e17;

int N, M;
int U[28], V[28];
ll K, W[28];
int p[10];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return 1;
}

int a[10];

ll mst() {
	ll ret = 0;
	for (int i = 0; i < 10; ++i) p[i] = -1;
	for (ll i = 0, u, v, w; i < N - 1; ++i) {
		u = U[a[i]], v = V[a[i]], w = W[a[i]];
		if (!join(u, v)) return INF;
		ret = (ret + w) % K;
	}
	return ret;
}

ll f(int d, int i) {
	if (d == N - 1) return mst();
	if (i == M) return INF;
	ll ret = f(d, i + 1);
	a[d] = i;
	ret = std::min(ret, f(d + 1, i + 1));
	return ret;
}

int main() {
	std::cin >> N >> M >> K;
	for (int i = 0; i < M; ++i) std::cin >> U[i] >> V[i] >> W[i];
	std::cout << f(0, 0);
}