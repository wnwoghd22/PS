#include <iostream>
#include <algorithm>
#include <cstring>

const int LEN = 4'000'000;
int N, M, K, p[LEN], A[LEN], k;

int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return false;

	if (a > b) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;

	return true;
}

int binary_search(int k) {
	int l = 0, r = M - 1, result = M - 1, mid;

	while (l <= r) {
		mid = (l + r) / 2;
		if (A[mid] > k) {
			result = std::min(result, mid);
			r = mid - 1;
		}
		else l = mid + 1;
	}
	return result;
}

int main() {
	memset(p, -1, sizeof p);
	std::cin >> N >> M >> K;
	for (int i = 0; i < M; ++i) std::cin >> A[i];
	std::sort(A, A + M);
	while (K--) {
		std::cin >> k;
		k = find(binary_search(k));
		std::cout << A[k] << '\n';
		join(k, k + 1);
	}
}