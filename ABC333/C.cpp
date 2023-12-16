#include <iostream>
#include <vector>

std::vector<std::string> S[13];
std::vector<std::string> A;

int main() {
	S[1].push_back("3");
	A.push_back("3");
	for (int i = 2; i <= 12; ++i) {
		for (const std::string& s : S[i - 1]) {
			S[i].push_back("1" + s);
		}
		for (int j = 1; j <= i; ++j) {
			S[i].push_back(std::string(i - j, '2') + std::string(j, '3'));
		}
		for (std::string& s : S[i]) A.push_back(s);
	}
	int N;
	std::cin >> N;
	std::cout << A[N - 1];
	
}