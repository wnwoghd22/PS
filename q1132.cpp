#include <iostream>
#include <algorithm>

typedef long long ll;

int N;
ll cnt[10];
bool not_null[10];
std::string s;
ll a[10];

int main() {
	std::cin >> N;
	while (N--) {
		std::cin >> s;
		for (int i = s.length() - 1, j = 1; i >= 0; --i, j *= 10) {
			cnt[s[i] - 'A'] += j;
			if (!i) not_null[s[i] - 'A'] = 1;
		}
	}
	// for (int i = 0; i < 10; ++i) std::cout << cnt[i] << ' ';
	// std::cout << '\n';

	ll min = 1e17;
	int k = -1;
	for (int i = 0; i < 10; ++i) {
		if (cnt[i] && !not_null[i] && cnt[i] < min) {
			k = i; min = cnt[i];
		}
	}
	int len = 0;
	for (int i = 0; i < 10; ++i) {
		if (i == k) continue;
		if (!cnt[i]) continue;
		a[len++] = cnt[i];
	}
	std::sort(a, a + len);
	int d = 9;
	ll sum = 0;
	for (int i = len - 1; i >= 0; --i) sum += a[i] * d--;
	sum += cnt[k] * d;

	std::cout << sum;
}