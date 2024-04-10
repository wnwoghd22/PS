#include <iostream>
#include <string>
#include <set>

std::set<std::string> st[11];
std::string n;
int k, len;

int main() {
	std::cin >> n >> k;
	len = n.length();

	st[0].insert(n);

	for (int i = 1; i <= k; ++i) {
		for (const std::string& s : st[i - 1]) {
			for (int j = 1; j < len; ++j) {
				if (s[j] == '0') continue;
				std::string t = s;
				std::swap(t[0], t[j]);
				st[i].insert(t);
			}
			for (int j = 1; j < len; ++j) {
				for (int l = j + 1; l < len; ++l) {
					std::string t = s;
					std::swap(t[j], t[l]);
					st[i].insert(t);
				}
			}
		}
	}
	int max = -1;
	for (const std::string& s : st[k]) {
		max = std::max(max, std::stoi(s));
	}
	std::cout << max;
}