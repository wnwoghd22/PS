#include <iostream>
#include <vector>

typedef long long ll;

int N, A;
std::vector<ll> stack;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> A;
		while (stack.size()) {
			if (stack.back() == A) {
				A += 1;
				stack.pop_back();
			}
			else break;
		}
		stack.push_back(A);
	}
	std::cout << stack.size();
}
