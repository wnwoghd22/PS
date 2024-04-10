#include <iostream>

typedef long long ll;
const int LEN = 100'001;

int N, A, sp;
struct E { ll min, sum; } stack[LEN];
ll S, ret;

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> A;
		S = 0;
		while (sp && stack[sp - 1].min >= A) {
			S += stack[sp - 1].sum;
			ret = std::max(ret, S * stack[sp - 1].min);
			--sp;
		}
		stack[sp++] = { A, S + A };
	}
	S = 0;
	while (sp--) {
		S += stack[sp].sum;
		A = stack[sp].min;
		ret = std::max(ret, S * A);
	}
	std::cout << ret;
}