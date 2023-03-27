#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

const int LEN = 100'001;

int N, M, t[LEN << 1], result[LEN];

void init() { 
	for (int i = N - 1; i > 0; --i)
		t[i] = t[i << 1] + t[i << 1 | 1];
}
void update(int p, int val) { 
	for (t[p += N] = val; p > 1; p >>= 1) 
		t[p >> 1] = t[p] + t[p ^ 1];
}
// [l,r)
int query(int l, int r) {
	int res = 0;
	for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res += t[l++];
		if (r & 1) res += t[--r];
	}
	return res;
}

int Q, K, I, J, V, q2;
struct Query1 { int i, v; };
struct Query2 { 
	int k, i, j, o;
	bool operator<(const Query2& r) const { return k < r.k; }
};
std::vector<Query1> queries1;
std::vector<Query2> queries2;

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> t[i + N];
	init();

	std::cin >> M;
	while (M--) {
		std::cin >> Q;
		if (Q == 1) {
			std::cin >> I >> V;
			queries1.push_back({ I, V });
		}
		if (Q == 2) {
			std::cin >> K >> I >> J;
			queries2.push_back({ K, I, J, q2++ });
		}
	}
	std::sort(queries2.begin(), queries2.end());
	for (int i = 0, j = 0; i <= queries1.size(); ++i) {
		while (j < queries2.size() && queries2[j].k == i) {
			result[queries2[j].o] = query(queries2[j].i - 1, queries2[j].j);
			++j;
		}
		if (i < queries1.size())
			update(queries1[i].i - 1, queries1[i].v);
	}
	for (int i = 0; i < q2; ++i) std::cout << result[i] << '\n';
}