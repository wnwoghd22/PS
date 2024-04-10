#include <iostream>

const int LEN = 2e5 + 1;
char S[LEN], stack[LEN];
int sp;

int main() {
	std::cin >> S;
	for (int i = 0; S[i]; ++i) {
		std::cout << S[i] << '\n';
		if (S[i] == 'C') {
			if (sp >= 2 && stack[sp - 2] == 'A' && stack[sp - 1] == 'B') {
				sp -= 2;
				// std::cout << "pop\n";
				continue;
			}
		}
		stack[sp++] = S[i];
		// stack[sp] = 0;
		// std::cout << stack << '\n';
	}
	stack[sp] = 0;
	std::cout << stack;
}