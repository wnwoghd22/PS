#include <iostream>
#include <cstring>

typedef long long ll;
const int LEN = 1e6 + 2;

int N, K, Q, A[LEN];
int L[LEN], R[LEN];
int p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
int join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return 1;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> K >> N;
	memset(p, -1, sizeof p);
	for (int i = 1; i <= N; ++i) {
		std::cin >> A[i];
		if (A[i] == A[i - 1]) join(i - 1, i);
		L[i] = i - 1; R[i] = i + 1;
	}
	ll ret = 0;
	std::cin >> Q;
	for (int i = 0, a, b, l, r; i < Q; ++i) {
		std::cin >> a >> b;
		if (a == 1) {
			p[find(b)] += 1;
			l = L[b], r = R[b];
			if (A[l] == A[r]) join(l, r);
			R[l] = r; L[r] = l;
		}
		if (a == 2) ret -= p[find(b)];
	}
	std::cout << ret;
}