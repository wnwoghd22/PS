#include <iostream>
#include <stack>

int main() {
	std::stack<char> S;
	int n, result = 0;
	char c;
	std::cin >> n;
	while (n--) {
		std::cin >> c;
		if (S.empty() || S.top() == c) S.push(c);
		else S.pop();
		result = std::max(result, (int)S.size());
	}
	if (S.size()) std::cout << -1;
	else std::cout << result;
}