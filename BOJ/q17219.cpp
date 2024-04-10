#include <iostream>
#include <map>

int main() {
	std::map<std::string, std::string> hash;
	int N, M;
	std::cin >> N >> M;
	while (N--) {
		std::string site, password;
		std::cin >> site >> password;
		hash[site] = password;
	}
	while (M--) {
		std::string site;
		std::cin >> site;
		std::cout << hash[site] << '\n';
	}
}