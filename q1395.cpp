#include <iostream>

const int MAX = 100'000;

int N, M;
int segTree[MAX * 4];
int lazy[MAX * 4];

void propagate(int index, int start, int end) {
	if (lazy[index]) {
		segTree[index] = end - start + 1 - segTree[index];
		if (start != end) {
			lazy[index * 2] ^= 1;
			lazy[index * 2 + 1] ^= 1;
		}
		lazy[index] = 0;
	}
}

void flip(int left, int right, int index = 1, int start = 1, int end = N) {
	propagate(index, start, end);

	if (left > end || right < start) return;
	if (left <= start && end <= right) {
		segTree[index] = end - start + 1 - segTree[index];
		if (start != end) {
			lazy[index * 2] ^= 1;
			lazy[index * 2 + 1] ^= 1;
		}
		return;
	}
	int mid = (start + end) / 2;
	flip(left, right, index * 2, start, mid);
	flip(left, right, index * 2 + 1, mid + 1, end);

	segTree[index] = segTree[index * 2] + segTree[index * 2 + 1];
}

int get_count(int left, int right, int start = 1, int end = N, int index = 1) {
	propagate(index, start, end);

	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return segTree[index];

	int mid = (start + end) / 2;
	return get_count(left, right, start, mid, index * 2) + get_count(left, right, mid + 1, end, index * 2 + 1);
}

int main() {
	int Q, s, t;
	std::cin >> N >> M;
	while (M--) {
		std::cin >> Q >> s >> t;
		if (Q) std::cout << get_count(s, t) << '\n';
		else flip(s, t);
	}
}