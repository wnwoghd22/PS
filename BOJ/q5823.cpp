#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

const int LEN = 150'000;
const int SQ = 400;

int N, L, M, pos[LEN], b_len;
int a[LEN], b[LEN], next[SQ * 2];

struct Bucket {
	int size;
	int A[SQ * 2];
	int cameras[SQ * 2];
	int cover[SQ * 2];

	int end() { return size ? pos[A[size - 1]] : 0; }
	int bound(int x) {
		int l = 0, r = size - 1, m;
		int k = size;
		while (l <= r) {
			m = l + r >> 1;
			if (pos[A[m]] > x) {
				k = std::min(k, m);
				r = m - 1;
			}
			else l = m + 1;
		}
		return k;
	}
	
	void update() {
		for (int l = 0, r = 0; l < size; ++l) {
			while (r < size && pos[A[r]] <= pos[A[l]] + L) ++r;
			next[l] = r;
		}
		for (int r = size - 1; r >= 0; --r) {
			cameras[r] = next[r] == size ? 1 : cameras[next[r]] + 1;
			cover[r] = next[r] == size ? pos[A[r]] + L : cover[next[r]];
		}
	}

	void pop(int a) {
		int k = -1;
		for (int i = 0; i < size; ++i) {
			if (A[i] == a) {
				k = i;
				break;
			}
		}
		size--;
		for (int i = k; i < size; ++i) A[i] = A[i + 1];
		update();
	}
	void push(int a) {
		int l = 0, r = size - 1, m;
		int k = size;
		while (l <= r) {
			m = l + r >> 1;
			if (pos[A[m]] > pos[a]) {
				k = std::min(k, m);
				r = m - 1;
			}
			else l = m + 1;
		}
		size++;
		for (int i = size - 1; i > k; --i) A[i] = A[i - 1];
		A[k] = a;
		update();
	}
	void push_back(int i) { A[size++] = i; }
} buckets[SQ];

void init() {
	for (int i = 0; i < b_len; ++i) buckets[i].size = 0;
	for (int i = 0; i < N; ++i) buckets[i / SQ].push_back(a[i]);
	for (int i = 0; i < b_len; ++i) buckets[i].update();
}

void normalize() {
	for (int i = 0, k = 0; i < b_len; ++i) {
		for (int j = 0; j < buckets[i].size; ++j, ++k) {
			a[k] = buckets[i].A[j];
			b[a[k]] = k / SQ;
		}
	}
	init();
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> L >> M;
	b_len = N / SQ + 1;
	for (int i = 0; i < N; ++i) {
		std::cin >> pos[i];
		a[i] = i;
		b[i] = i / SQ;
	}
	init();
	for (int q = 0, j = 0, i, y, s, x, S; q < M; ++q, ++j) {
		if (j == SQ - 1) j = 0, normalize();
		std::cin >> i >> y;
		buckets[b[i]].pop(i);
		pos[i] = y;
		b[i] = b_len - 1;
		for (int kk = 0; kk < b_len; ++kk) {
			if (y <= buckets[kk].end()) {
				b[i] = kk;
				break;
			}
		}
		buckets[b[i]].push(i);

		s = buckets[0].cameras[0];
		x = buckets[0].cover[0];
		for (int kk = 1, k; kk < b_len; ++kk) {
			if (!buckets[kk].size || buckets[kk].end() <= x) continue;
			k = buckets[kk].bound(x);
			s += buckets[kk].cameras[k];
			x = buckets[kk].cover[k];
		}
		std::cin >> S;
		if (s != S) {
			std::cout << "Incorrect: " << q << ' ' << "expected: " << S << ' ' << "output: " << s;
			return 0;
		}
		// std::cout << s << '\n';
	}
	std::cout << "Correct";
}