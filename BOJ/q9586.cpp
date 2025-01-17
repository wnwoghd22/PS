#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

typedef long long ll;
const int LEN = 100'001;

int N, idx;
int A[LEN], S[LEN], nxt[32][LEN];
std::map<int, int> map;
std::vector<int> arr[LEN];

int lower_bound(int i, int x) {
	int l = 0, r = arr[i].size() - 1, m, ret = -1;
	while (l <= r) {
		m = (l + r) / 2;
		if (arr[i][m] >= x) {
			ret = m;
			r = m - 1;
		}
		else {
			l = m + 1;
		}
	}
	return ret;
}

int upper_bound(int i, int x) {
	int l = 0, r = arr[i].size() - 1, m, ret = -1;
	while (l <= r) {
		m = (l + r) / 2;
		if (arr[i][m] <= x) {
			ret = m;
			l = m + 1;
		}
		else {
			r = m - 1;
		}
	}
	return ret;
}


ll query(int i, int x, int l, int r) {
	if (map.find(x ^ S[i - 1]) == map.end()) return 0;
	int k = map[x ^ S[i - 1]];

	int s = lower_bound(k, l);
	int e = upper_bound(k, r);

	if (s == -1 || e == -1 || s > e) return 0;

	return e - s + 1;
}

int main() {
	// freopen("hack.in", "r", stdin);
	// freopen("hack.out", "w", stdout);

	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		std::cin >> A[i];
		S[i] = A[i] ^ S[i - 1];
		if (map.find(S[i]) == map.end()) map[S[i]] = idx++;
		arr[map[S[i]]].push_back(i);
		for (int j = 0; j < 32; ++j) {
			if (~A[i] & (1 << j)) nxt[j][i] = i;
			else nxt[j][i] = N + 1;
		}
	}
	for (int j = 0; j < 32; ++j) {
		for (int i = N; i > 0; --i)
			if (nxt[j][i - 1] == N + 1)
				nxt[j][i - 1] = nxt[j][i];
	}

	ll ret = 0;
	for (int i = 1; i <= N; ++i) {
		int k = A[i], l = i, r, b;
		while (1) {
			r = N;
			for (int j = 0; j < 32; ++j) {
				if (k & (1 << j)) {
					b = j;
					r = std::min(r, nxt[j][i] - 1);
				}
			}
			
			ll cur = query(i, k, l, r);
			ret += cur;

			if (!k || r == N) break;
			else {
				for (int j = 0; j < 32; ++j)
					if (k & (1 << j) && nxt[j][i] - 1 == r)
						k ^= 1 << j;
				l = r + 1;
			}
		}
	}
	std::cout << ret;
}