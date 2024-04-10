#include <iostream>
#include <vector>
#include <set>

std::set<std::string> S;
std::vector<std::string> ret;

int main() {
	int N;
	std::cin >> N;
	while (N--) {
		std::string name, log;
		std::cin >> name >> log;
		if (log == "enter") S.insert(name);
		if (log == "leave") S.erase(name);
	}
	for (const std::string& name : S) ret.push_back(name);
	for (int i = ret.size() - 1; i >= 0; --i) std::cout << ret[i] << '\n';
}