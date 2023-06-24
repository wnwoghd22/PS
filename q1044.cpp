#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

typedef long long ll;
typedef std::pair<ll, ll> pll;
const ll INF = 1e17;
const int LEN = 20;

int N;
ll A1[LEN], A2[LEN], B1[LEN], B2[LEN];
std::map<ll, ll> V1[LEN], V2[LEN];
std::vector<pll> lis[LEN];
int lower_bound(int i, ll d) {
	int l = 0, r = lis[i].size(), m;
	while (l < r) {
		m = l + r >> 1;
		if (lis[i][m].first >= -d) r = m;
		else l = m + 1;
	}
	return r;
}

void f1(int i, ll Sa, ll Sb, int depth, ll bit) {
	if (i == N / 2) {
		if (V1[depth].find(Sa - Sb) != V1[depth].end())
			V1[depth][Sa - Sb] = std::min(V1[depth][Sa - Sb], bit);
		else V1[depth][Sa - Sb] = bit;
		return;
	}
	f1(i + 1, Sa + A1[i], Sb, depth + 1, bit << 1);
	f1(i + 1, Sa, Sb + B1[i], depth, bit << 1 | 1);
}
void f2(int i, ll Sa, ll Sb, int depth, ll bit) {
	if (i == N / 2) {
		if (V2[depth].find(Sa - Sb) != V2[depth].end())
			V2[depth][Sa - Sb] = std::min(V2[depth][Sa - Sb], bit);
		else V2[depth][Sa - Sb] = bit;
		return;
	}
	f2(i + 1, Sa + A2[i], Sb, depth + 1, bit << 1);
	f2(i + 1, Sa, Sb + B2[i], depth, bit << 1 | 1);
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N / 2; ++i) std::cin >> A1[i];
	for (int i = 0; i < N / 2; ++i) std::cin >> A2[i];
	for (int i = 0; i < N / 2; ++i) std::cin >> B1[i];
	for (int i = 0; i < N / 2; ++i) std::cin >> B2[i];

	f1(0, 0, 0, 0, 0), f2(0, 0, 0, 0, 0);
	for (int i = 0; i <= N / 2; ++i) {
		for (const auto& [d, b] : V2[i]) {
			lis[i].push_back({ d, b });
		}
		std::sort(lis[i].begin(), lis[i].end());
	}

	ll dif = INF, bit = (1ll << N) - 1;
	for (int i = 0; i <= N / 2; ++i) {
		for (const auto& [d1, b1] : V1[N / 2 - i]) {
			std::cout << "L: " << d1 << ' ' << b1 << '\n';
			int ptr = lower_bound(i, d1);
			if (ptr >= lis[i].size()) 
				ptr = lis[i].size() - 1;
			const auto& [d2, b2] = lis[i][ptr];
			std::cout << "R: " << d2 << ' ' << b2 << '\n';
			ll cur_dif = abs(d1 + d2), cur_bit = b1 << (N >> 1) | b2;
			std::cout << "dif: " << dif << ", cur: " << cur_dif << '\n';
			std::cout << "bit: " << bit << ", cur: " << cur_bit << '\n';
			if (cur_dif < dif)
				dif = cur_dif, bit = cur_bit;
			else if (cur_dif == dif && cur_bit < bit)
				bit = cur_bit;
			
			if (ptr > 0) {
				const auto& [d2, b2] = lis[i][ptr - 1];
				std::cout << "R: " << d2 << ' ' << b2 << '\n';
				ll cur_dif = abs(d1 + d2), cur_bit = b1 << (N >> 1) | b2;
				std::cout << "dif: " << dif << ", cur: " << cur_dif << '\n';
				std::cout << "bit: " << bit << ", cur: " << cur_bit << '\n';
				if (cur_dif < dif)
					dif = cur_dif, bit = cur_bit;
				else if (cur_dif == dif && cur_bit < bit)
					bit = cur_bit;
			}
			if (ptr < lis[i].size() - 1) {
				const auto& [d2, b2] = lis[i][ptr + 1];
				std::cout << "R: " << d2 << ' ' << b2 << '\n';
				ll cur_dif = abs(d1 + d2), cur_bit = b1 << (N >> 1) | b2;
				std::cout << "dif: " << dif << ", cur: " << cur_dif << '\n';
				std::cout << "bit: " << bit << ", cur: " << cur_bit << '\n';
				if (cur_dif < dif)
					dif = cur_dif, bit = cur_bit;
				else if (cur_dif == dif && cur_bit < bit)
					bit = cur_bit;
			}
		}
	}
	std::cout << bit << '\n';
	for (int i = N - 1; i >= 0; --i) std::cout << !!(bit & 1ll << i) + 1 << ' ';
}