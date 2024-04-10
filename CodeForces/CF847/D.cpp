#include <iostream>
#include <map>

typedef long long int ll;

ll solve() {
	std::map<int, ll> seq;
	ll n, a;
	std::cin >> n;
	while (n--) {
		std::cin >> a;
		if (seq.find(a) == seq.end()) seq[a] = 0;
		++seq[a];
	}
	ll result = 0, cur = -1, h = 0;
	for (const auto& [k, v] : seq) {
		if (cur + 1 != k) h = 0;
		if (v > h) result += v - h;
		h = v;
		cur = k;
	}
	return result;
}

int main() {
	int T;
	std::cin >> T;
	while (T--) std::cout << solve() << '\n';
}