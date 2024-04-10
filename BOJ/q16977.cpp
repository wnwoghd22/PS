#include <iostream>
#include <algorithm>
#include <cstring>

const int LEN = 100'001;

int N, H[LEN];
int sp, idx[LEN], c[LEN], ptr[LEN], nx[LEN];
void merge(int l, int m, int r) {
	int i = l, j = m + 1, k = l;
	while (i <= m && j <= r) ptr[k++] = H[idx[i]] > H[idx[j]] ? idx[i++] : idx[j++];
	while (i <= m) ptr[k++] = idx[i++];
	while (j <= r) ptr[k++] = idx[j++];
	for (i = l; i <= r; ++i) idx[i] = ptr[i];
}
void merge_sort(int l, int r) {
	if (l < r) {
		int m = l + r >> 1;
		merge_sort(l, m);
		merge_sort(m + 1, r);
		merge(l, m, r);
	}
}

struct Node {
	int m, lm, rm, f;
	Node operator+(const Node& r) const {
		return {
			std::max({ m, r.m, rm + r.lm }),
			f ? m + r.lm : lm,
			r.f ? rm + r.m : r.rm,
			f & r.f
		};
	}
} seg_tree[LEN << 2];

void update(int x, int d, int s = 1, int e = N, int i = 1) {
	if (x < s || e < x) return;
	if (s == e) { seg_tree[i] = { d, d, d, d }; return; }
	int m = s + e >> 1;
	update(x, d, s, m, i << 1); update(x, d, m + 1, e, i << 1 | 1);
	seg_tree[i] = seg_tree[i << 1] + seg_tree[i << 1 | 1];
}

Node get(int l, int r, int s = 1, int e = N, int i = 1) {
	if (r < s || e < l) return { 0, 0, 0, 0 };
	if (l <= s && e <= r) return seg_tree[i];
	int m = s + e >> 1;
	return get(l, r, s, m, i << 1) + get(l, r, m + 1, e, i << 1 | 1);
}

int Q, R, ql[LEN], qr[LEN], w[LEN], l[LEN], r[LEN], qp, qptr[LEN], qn[LEN];

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		std::cin >> H[i];
		idx[i] = i;
	}
	merge_sort(1, N);
	memset(ptr, -1, sizeof ptr);
	for (int i = 1; i <= N; ++i) std::cout << idx[i] << ' '; std::cout << '\n';
	for (int i = 1; i <= N; ++i) std::cout << H[idx[i]] << ' '; std::cout << '\n';

	for (int i = 1, h = 0; i <= N; ++i) {
		if (H[idx[i]] ^ h) c[sp++] = h = H[idx[i]];
		nx[idx[i]] = ptr[sp - 1];
		ptr[sp - 1] = idx[i];
	}
	std::cin >> Q;
	for (int i = 0; i < Q; ++i) {
		std::cin >> ql[i] >> qr[i] >> w[i];
		r[i] = sp;
	}
	while (1) {
		R = 0;
		memset(qptr, -1, sizeof qptr);
		for (int i = 0, m; i < Q; ++i) {
			if (l[i] < r[i]) {
				R++;
				m = l[i] + r[i] >> 1;
				qn[i] = qptr[m];
				qptr[m] = i;
			}
		}
		if (!R) break;

		memset(seg_tree, 0, sizeof seg_tree);
		for (int m = 0, i; m < sp; ++m) {
			i = ptr[m];
			while (~i) {
				update(i, 1);
				i = nx[i];
			}
			i = qptr[m];
			while (~i) {
				if (get(ql[i], qr[i]).m >= w[i]) r[i] = m;
				else l[i] = m + 1;
				i = qn[i];
			}
		}
	}
	for (int i = 0; i < Q; ++i) std::cout << c[r[i]] << '\n';
}