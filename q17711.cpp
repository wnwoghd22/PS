#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <queue>

const int B_CNT = 500;
const int B_LEN = 800;

int N, Q;
int X[B_CNT * B_LEN];
std::priority_queue<int> buffer[B_CNT];
std::priority_queue<int> bucket[B_CNT];

int push_bucket(int b_idx, int p) {
	if (p >= bucket[b_idx].top()) return p;
	buffer[b_idx].push(-p);
	int top = bucket[b_idx].top();
	bucket[b_idx].pop();
	bucket[b_idx].push(p);
	return top;
}

void flush(int b_idx) {
	if (buffer[b_idx].empty()) return;

	int _l = b_idx * B_LEN;
	int _r = std::min(_l + B_LEN, N);
	for (int i = _l; i < _r; ++i) {
		if (X[i] > -buffer[b_idx].top()) {
			buffer[b_idx].push(-X[i]);
			X[i] = -buffer[b_idx].top();
			buffer[b_idx].pop();
		}
	}
	buffer[b_idx] = std::priority_queue<int>();
}
void preprocess(int b_idx) {
	int _l = b_idx * B_LEN;
	int _r = std::min(_l + B_LEN, N);

	bucket[b_idx] = std::priority_queue<int>();
	for (int i = _l; i < _r; ++i) bucket[b_idx].push(X[i]);
}

int push(int b_idx, int l, int r, int p) {
	flush(b_idx);

	for (int i = l; i <= r; ++i) {
		if (X[i] > p)
			std::swap(X[i], p);
	}

	preprocess(b_idx);

	return p;
}

int query(int l, int r, int p) {
	for (int b_idx = l / B_LEN; b_idx * B_LEN <= r; ++b_idx) {
		int _l = std::max(l, b_idx * B_LEN);
		int _r = std::min((b_idx + 1) * B_LEN - 1, r);
		if (_l + B_LEN == _r + 1) p = push_bucket(b_idx, p);
		else p = push(b_idx, _l, _r, p);
	}
	return p;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> Q;
	for (int i = 0; i < N; ++i) {
		std::cin >> X[i];
		bucket[i / B_LEN].push(X[i]);
	}

	for (int q = 0, s, t, p; q < Q; ++q) {
		std::cin >> s >> t >> p;
		s--, t--;
		if (s > t) {
			p = query(s, N - 1, p);
			p = query(0, t, p);
		}
		else p = query(s, t, p);
		std::cout << p << '\n';
	}
}