#include <iostream>
#include <vector>

typedef long long int ll;

ll K, H, Q, A, B, bound;

int get_path(ll a, ll b) {
	if (a >= bound || b >= bound) return -1;
	if (a == b) return 0;
	std::vector<int> convA, convB;
	while (a) convA.push_back(a % (K + 1)), a /= (K + 1);
	while (b) convB.push_back(b % (K + 1)), b /= (K + 1);

	convB.push_back(0);
	while (convA.size() != convB.size()) convA.push_back(0);
	int lca = convB.size() - 1;
	int digit_a = 0, digit_b = 0;
	while (!convA[digit_a]) digit_a++;
	while (!convB[digit_b]) digit_b++;
	while (lca > std::max(digit_a, digit_b) + 1) {
		if (convA[lca - 1] != convB[lca - 1]) break;
		lca--;
	}
	return lca * 2 - digit_a - digit_b;
}

int main() {
	std::cin >> K >> H >> Q;
	bound = pow(K + 1, H);
	while (Q--) {
		std::cin >> A >> B;
		std::cout << get_path(A, B) << '\n';
	}
}