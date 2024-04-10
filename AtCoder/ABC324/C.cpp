#include <iostream>
#include <string>

bool valid(const std::string& t, const std::string& s) {
	if (t.length() == s.length()) {
		int err = 1;
		for (int i = 0; i < t.length(); ++i) if (t[i] ^ s[i]) --err;
		return err >= 0;
	}
	if (t.length() > s.length()) {
		if (t.length() - s.length() != 1) return false;
		for (int i = 0, j = 0; i < s.length(); ++i, ++j) {
			if (s[i] ^ t[j]) {
				if (i ^ j) return false;
				--i;
			}
		}
	}
	else {
		if (s.length() - t.length() != 1) return false;
		for (int i = 0, j = 0; i < t.length(); ++i, ++j) {
			if (t[i] ^ s[j]) {
				if (i ^ j) return false;
				--i;
			}
		}
	}
	return true;
}

int N, M, A[500000];
std::string T, S;

int main() {
	std::cin >> N >> T;
	for (int i = 1; i <= N; ++i) {
		std::cin >> S;
		if (valid(T, S)) A[M++] = i;
	}
	std::cout << M << '\n';
	for (int i = 0; i < M; ++i) {
		std::cout << A[i] << ' ';
	}
}