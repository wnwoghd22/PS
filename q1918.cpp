#include <iostream>
#include <stack>

int main() {
	std::stack<char> S;
	std::string expr;
	std::cin >> expr;

	std::string post = "";
	for (const char& c : expr) {
		switch (c) {
		case '+': case '-':
			while (!S.empty() && S.top() != '(') post += S.top(), S.pop();
			S.push(c);
			break;
		case '*': case '/':
			while (!S.empty() && (S.top() == '*' || S.top() == '/')) post += S.top(), S.pop();
			S.push(c);
			break;
		case '(':
			S.push('(');
			break;
		case ')':
			while (!S.empty() && S.top() != '(') post += S.top(), S.pop();
			if (!S.empty()) S.pop();
			break;
		default:
			post += c;
			break;
		}
	}
	while (!S.empty()) post += S.top(), S.pop();

	std::cout << post;
}