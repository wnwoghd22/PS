#include <iostream>

const int MAX = 2'000'000;
int segTree[MAX * 4];

void push(int n, int index = 1, int start = 1, int end = MAX) {
	if (n > end || n < start) return;
	if (start <= n && n <= end) ++segTree[index];
	if (start == end) return;

	int mid = (start + end) / 2;
	push(n, index * 2, start, mid);
	push(n, index * 2 + 1, mid + 1, end);
}

int pop(int k, int start = 1, int end = MAX, int index = 1) {
	if (k > segTree[index]) return -1;

	--segTree[index];
	if (start == end) return start;

	int mid = (start + end) / 2;
	int l = pop(k, start, mid, index * 2);
	if (l != -1) return l;

	int r = pop(k - segTree[index * 2], mid + 1, end, index * 2 + 1);
	return r;
}

int main() {
	int N;
	std::cin >> N;
	while (N--) {
		int T, X;
		std::cin >> T >> X;

		if (T == 1) push(X);
		if (T == 2) std::cout << pop(X) << '\n';
	}
}