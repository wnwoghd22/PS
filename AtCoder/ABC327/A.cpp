#include <iostream>
#include <string>

int N;
std::string S;

int main() {
	std::cin >> N >> S;
	for (int i = 0; i < S.size() - 1; ++i) {
		if (S[i] == 'a' && S[i + 1] == 'b' || S[i] == 'b' && S[i + 1] == 'a') {
			std::cout << "YES";
			return 0;
		}
	}
	std::cout << "NO";
}