#include <iostream>
#include <algorithm>

int N;
std::string S[50];
int f(const std::string& s) {
	int ret = 0;
	for (const char& c : s)
		if (c >= '0' && c <= '9') ret += c - '0';
	return ret;
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> S[i];
	std::sort(S, S + N, [](const std::string& l, const std::string& r) {
		return l.length() == r.length() ?
			f(l) == f(r) ? l < r : f(l) < f(r) :
			l.length() < r.length();
		}
	);
	for (int i = 0; i < N; ++i) std::cout << S[i] << '\n';
}