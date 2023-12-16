#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 2e5 + 1;

int N, t[LEN], x[LEN];
int ptr[LEN], prev[LEN], used[LEN];
int seg_max[LEN << 2];
int lazy[LEN << 2];
ll s;

void propagate(int s, int e, int i) {
	if (lazy[i]) {
		seg_max[i] += lazy[i];
		if (s ^ e) {
			lazy[i << 1] += lazy[i];
			lazy[i << 1 | 1] += lazy[i];
		}
		lazy[i] = 0;
	}
}

void update(int l, int r, short d, int s = 1, int e = N, int i = 1) {
	propagate(s, e, i);
	if (e < l || r < s) return;
	if (l <= s && e <= r) {
		seg_max[i] += d;
		if (s ^ e) {
			lazy[i << 1] += d;
			lazy[i << 1 | 1] += d;
		}
		return;
	}
	int m = s + e >> 1;
	update(l, r, d, s, m, i << 1);
	update(l, r, d, m + 1, e, i << 1 | 1);
	seg_max[i] = std::max(seg_max[i << 1], seg_max[i << 1 | 1]);
}

inline int get_max() { return seg_max[1]; }


int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		std::cin >> t[i] >> x[i];
		if (t[i] == 1) {
			prev[i] = ptr[x[i]];
			ptr[x[i]] = i;
		}
		if (t[i] == 2) {
			int pos = ptr[x[i]];
			int cur_pos = ptr[x[i]];
			// std::cout << "encountered, ";
			// std::cout << "type: " << x[i] << ' ';
			while (used[cur_pos]) {
				cur_pos = prev[cur_pos];
				prev[pos] = cur_pos;
				if (!cur_pos) break;
			}
			if (!cur_pos) {
				std::cout << -1;
				return 0;
			}
			// std::cout << "potion pos: " << cur_pos << '\n';
			used[cur_pos] = 1;
			update(cur_pos, i, 1);
		}
	}
	std::cout << get_max() << '\n';
	for (int i = 1; i <= N; ++i) {
		if (t[i] == 1) std::cout << used[i] << ' ';
	}
}