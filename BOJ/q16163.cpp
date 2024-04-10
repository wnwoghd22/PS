#include <iostream>

typedef long long int ll;
const int LEN = 4'000'002;
int A[LEN];

int manachers(std::string s) {
	int len = s.length(), r = 0, p = 0, result = 0;

	for (int i = 0; i < len; ++i) {
		A[i] = i <= r ? std::min(A[2 * p - i], r - i) : 0;
		while (i - A[i] - 1 >= 0 && i + A[i] + 1 < len && s[i - A[i] - 1] == s[i + A[i] + 1]) A[i]++;
		if (r < i + A[i]) r = i + A[i], p = i;
		result = std::max(result, A[i]);
	}
	return result;
}
int main() {
	std::string S;
	std::string s = "#";
	std::cin >> S;
	for (const char& c : S) s += c, s += "#";
	manachers(s);
	ll count = 0;
	for (int i = 0; i < s.length(); ++i) count += (A[i] + 1) / 2;
	std::cout << count;
}