#include <iostream>
#include <stack>

int A[26];

int main() {
	std::cout << std::fixed;
	std::cout.precision(2);

	int N;
	std::string expr;
	std::cin >> N >> expr;
	for (int i = 0; i < N; ++i) std::cin >> A[i];

	std::stack<double> S;
	for (const char& c : expr) {
		double a, b;
		switch (c) {
		case '+':
			a = S.top(); S.pop();
			b = S.top(); S.pop();
			S.push(b + a);
			break;
		case '-':
			a = S.top(); S.pop();
			b = S.top(); S.pop();
			S.push(b - a);
			break;
		case '*':
			a = S.top(); S.pop();
			b = S.top(); S.pop();
			S.push(b * a);
			break;
		case '/':
			a = S.top(); S.pop();
			b = S.top(); S.pop();
			S.push(b / a);
			break;
		default:
			S.push(A[c - 'A']);
		}
	}
	std::cout << S.top();
}
