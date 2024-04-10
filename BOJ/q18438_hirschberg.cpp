#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

std::string S, T, lcs;
void hirschberg(int u, int d, int l, int r) {
	if (u > d) return;
	if (u == d) { // only one row
		for (int j = l; j <= r; ++j) {
			if (S[u] == T[j]) {
				lcs += S[u];
				break;
			}
		}
		return;
	}
	int mid = u + d >> 1;
	std::vector<int> L(r - l + 3), R(r - l + 3), pre(r - l + 3);
	for (int i = u; i <= mid; ++i) {
		for (int j = l; j <= r; ++j) {
			if (S[i] == T[j]) L[j - l + 1] = pre[j - l] + 1;
			else L[j - l + 1] = std::max(L[j - l], pre[j - l + 1]);
		}
		pre = L;
	}
	std::fill(pre.begin(), pre.end(), 0);
	for (int i = d; i > mid; --i) {
		for (int j = r; j >= l; --j) {
			if (S[i] == T[j]) R[j - l + 1] = pre[j - l + 2] + 1;
			else R[j - l + 1] = std::max(R[j - l + 2], pre[j - l + 1]);
		}
		pre = R;
	}
	int max = -1, idx = 0;
	for (int i = l; i <= r + 1; ++i) {
		if (L[i - l] + R[i - l + 1] > max) {
			max = L[i - l] + R[i - l + 1];
			idx = i;
		}
	}
	hirschberg(u, mid, l, idx - 1);
	hirschberg(mid + 1, d, idx, r);
}

int main() {
	std::cin >> S >> T;
	hirschberg(0, S.length() - 1, 0, T.length() - 1);
	std::cout << lcs.length() << '\n';
	std::cout << lcs;
}