#include <iostream>

typedef long long int ll;
const ll MAX = 1e18;

int main() {
	ll Q, bound_u = MAX + 1, bound_l = -MAX - 1, t = -1, p = -1, x;
	char c;
	std::cin >> Q;
	for (int i = 1; i <= Q; ++i) {
		std::cin >> x >> c;
		if (c == '^') bound_l = std::max(bound_l, x);
		if (c == 'v') bound_u = std::min(bound_u, x);
		if (!~t && bound_u - bound_l == 2) t = i;
		if (!~p && bound_u - bound_l < 2) p = i;
	}
	if (~p) std::cout << "Paradox!\n" << p;
	else if (~t) std::cout << "I got it!\n" << t;
	else std::cout << "Hmm...";
}