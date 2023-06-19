#include <iostream>
#include <vector>

typedef long long int ll;
const ll INF = 1e17;
const int LEN = 20;

int N;
ll A1[LEN], A2[LEN], B1[LEN], B2[LEN];
std::vector<std::pair<ll, int>> V1[LEN], V2[LEN];

void f1(int i, ll Sa, ll Sb, int depth, int bit) {
	if (i == N / 2) {
		V1[depth].push_back({ Sa - Sb, bit });
		return;
	}
	f1(i + 1, Sa + A1[i], Sb, depth + 1, bit | 1 << i);
	f1(i + 1, Sa, Sb + B1[i], depth, bit);
}
void f2(int i, ll Sa, ll Sb, int depth, int bit) {
	if (i == N / 2) {
		V2[depth].push_back({ Sa - Sb, bit });
		return;
	}
	f2(i + 1, Sa + A2[i], Sb, depth + 1, bit | 1 << i);
	f2(i + 1, Sa, Sb + B2[i], depth, bit);
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N / 2; ++i) std::cin >> A1[i];
	for (int i = 0; i < N / 2; ++i) std::cin >> A2[i];
	for (int i = 0; i < N / 2; ++i) std::cin >> B1[i];
	for (int i = 0; i < N / 2; ++i) std::cin >> B2[i];

	f1(0, 0, 0, 0, 0), f2(0, 0, 0, 0, 0);

	ll dif = INF; int bit1 = 0, bit2 = 0;
	for (int i = 0; i <= N / 2; ++i) {
		for (const auto& [d1, b1] : V1[N / 2 - i]) {
			for (const auto& [d2, b2] : V2[i]) {
				ll cur_dif = abs(d1 + d2);
				if (cur_dif < dif)
					dif = cur_dif, bit1 = b1, bit2 = b2;
			}
		}
	}
	for (int i = 0; i < N / 2; ++i) std::cout << !(bit1 & 1 << i) + 1 << ' ';
	for (int i = 0; i < N / 2; ++i) std::cout << !(bit2 & 1 << i) + 1 << ' ';
}