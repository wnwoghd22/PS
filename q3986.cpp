#include <iostream>
#include <stack>

int main() {
	int T, result = 0;
	std::cin >> T;
	while (T--) {
		std::string S;
		std::cin >> S;
		std::stack<char> _s;
		for (const char& c : S) {
			if (_s.empty() || _s.top() != c) _s.push(c);
			else _s.pop();
		}
		if (!_s.size()) result++;
	}
	std::cout << result;
}