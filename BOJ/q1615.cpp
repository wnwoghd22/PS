#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 2'001;

int N, M, K, A[LEN * LEN >> 1];
ll S, t[LEN];
ll sum(int i) { ll r = 0; while (i > 0) r += t[i], i -= i & -i; return r; }
void update(int i, ll d) { while (i <= N) t[i] += d, i += i & -i; }

int main() {
	std::cin >> N >> M;
	for (int i = 0, a, b; i < M; ++i) std::cin >> a >> b, A[i] = a * LEN + b;
	std::sort(A, A + M);

	for (int i = 0; i < M; ++i) S += i - sum(A[i] % LEN), update(A[i] % LEN, 1); 
	std::cout << S;
}