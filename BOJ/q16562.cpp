#include <iostream>
#include <algorithm>
#include <cstring>

const int LEN = 10'001;

int N, M, K, S, A[LEN];

int p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	if (p[a] > p[b]) std::swap(a, b);
	p[a] += p[b], p[b] = a, A[a] = std::min(A[a], A[b]);
	return 1;
}

int main() {
	std::cin >> N >> M >> K;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	memset(p, -1, sizeof p);
	for (int i = 0, v, w; i < M; ++i) {
		std::cin >> v >> w;
		join(v, w);
	}
	for (int i = 1; i <= N; ++i)
		if (i == find(i)) S += A[i];
	
	if (S <= K) std::cout << S;
	else std::cout << "Oh no";
}