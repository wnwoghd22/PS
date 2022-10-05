#include <iostream>
#include <vector>

const int MAX = 100'000;
int segTree[MAX * 4];
int length() { return segTree[1]; }

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
	int N, K, current;
	std::vector<int> order;
	std::cin >> N >> K;
	current = K;

	for (int i = 1; i <= N; ++i) push(i);

	while (true) {
		std::cout << length() << ' ' << current << '\n';

		order.push_back(pop(current));
		if (length() == 0) break;
		current = current + K - 1;
		current %= length();
		if (!current) current = length();
	}

	std::cout << "<";
	for (int i = 0; i < N; ++i) {
		std::cout << order[i];
		if (i != N - 1) std::cout << ", ";
	}
	std::cout << ">";

}