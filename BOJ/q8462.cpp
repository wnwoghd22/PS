#include <iostream>
#include <cmath>
#include <algorithm>

typedef long long int ll;
const int LEN = 100'001;
const int MAX = 1'000'001;

ll N, t, sqrtN, A[LEN], answer[LEN], count[MAX], sum = 0;

void push(int n) { sum -= count[n] * count[n] * n; ++count[n]; sum += count[n] * count[n] * n; }
void pop(int n) { sum -= count[n] * count[n] * n; --count[n]; sum += count[n] * count[n] * n; }

struct Query {
	int index, s, e;
	bool operator<(const Query& r) { return s / sqrtN ^ r.s / sqrtN ? s / sqrtN < r.s / sqrtN : e < r.e; }
} q[LEN];

int main() {
	std::cin >> N >> t;
	sqrtN = sqrt(N);
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	for (int i = 0; i < t; ++i) {
		q[i].index = i;
		std::cin >> q[i].s >> q[i].e;
	}
	std::sort(q, q + t);
	int s = q[0].s, e = q[0].e;
	for (int i = s; i <= e; ++i) push(A[i]);
	answer[q[0].index] = sum;
	for (int i = 1; i < t; ++i) {
		while (s < q[i].s) pop(A[s++]);
		while (s > q[i].s) push(A[--s]);
		while (e < q[i].e) push(A[++e]);
		while (e > q[i].e) pop(A[e--]);
		answer[q[i].index] = sum;
	}
	for (int i = 0; i < t; ++i) std::cout << answer[i] << '\n';
}