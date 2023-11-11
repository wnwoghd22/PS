#include <iostream>
#include <cstring>

const int LEN = 2e5 + 1;
typedef long long ll;

int N, Q;
ll W[LEN];
int P[LEN];
int find(int x) {
	int y, g;
	if (P[x] < 0) return x;
	y = P[x];
	g = find(y);
	W[x] += W[y];
	return P[x] = g;
}
int join(int x, int y, int w) {
	int i, j;
	i = find(x);
	j = find(y);
	if (i == j) return 0;
	if (P[i] < P[j]) {
		P[i] += P[j];
		P[j] = i;
		W[j] = -W[y] + w + W[x];
	}
	else {
		P[j] += P[i];
		P[i] = j;
		W[i] = W[y] - w - W[x];
	}
	return 1;
}

int sp, ans[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> Q;
	memset(P, -1, sizeof P);
	for (int i = 1, a, b, d; i <= Q; ++i) {
		std::cin >> a >> b >> d;
		if (find(a) == find(b)) {
			ll diff = W[b] - W[a];
			if (diff != d) continue;
		}
		else join(a, b, d);
		ans[sp++] = i;
	}
	for (int i = 0; i < sp; ++i) std::cout << ans[i] << ' ';
}