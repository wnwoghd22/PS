#include <iostream>
#include <string>
#include <vector>

int main() {
	std::string s;
	getline(std::cin, s);
	// std::cout << s;

	std::vector<std::string> stack;
	bool flag = false;
	for (int i = 0; i < s.length(); ++i) {
		char c = s[i];
		if (c == '<' || c == '>' || c == '(' || c == ')') {
			flag = false;
			stack.push_back(std::string(1, c));
		}
		else if (c == '|') {
			++i;
			flag = false;
			stack.push_back("||");
		}
		else if (c == '&') {
			++i;
			flag = false;
			stack.push_back("&&");
		}
		else if (c == ' ') {
			flag = false;
		}
		else {
			if (flag) {
				stack.back() += c;
			}
			else stack.push_back(std::string(1, c));
			flag = true;
		}
	}
	for (const std::string& token : stack) std::cout << token << ' ';
}