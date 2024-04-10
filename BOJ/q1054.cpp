#include <iostream>
#include <map>

typedef long long ll;

int N;
std::string t[13];
std::map<std::string, ll> dpL[1 << 13];
std::map<std::string, ll> dpR[1 << 13];

ll fL(std::string, int);
ll fR(std::string, int);

bool is_palindrome(const std::string& s) {
	int l = 0, r = s.length() - 1;
	while (l < r) {
		if (s[l] != s[r]) return false;
		++l; --r;
	}
	return true;
}

ll fL(std::string s, int b) {
	if (b == (1 << N) - 1) return is_palindrome(s); // all words are used, then token should be null
	if (dpL[b].find(s) != dpL[b].end()) return dpL[b][s];
	ll& ref = dpL[b][s] = 0;

	if (is_palindrome(s)) ++ref;

	for (int i = 0; i < N; ++i) {
		if (b & 1 << i) continue;
		
		if (t[i].length() <= s.length()) {
			if (s.rfind(t[i], 0) == 0) // if t is prefix
				ref += fL(s.substr(t[i].length()), b | 1 << i);
		}
		else {
			if (t[i].rfind(s, 0) == 0) { // if s is prefix
				std::string r = t[i].substr(s.length());
				std::reverse(r.begin(), r.end());
				ref += fR(r, b | 1 << i);
			}
		}
	}
	return ref;
}

ll fR(std::string s, int b) {
	if (b == (1 << N) - 1) return is_palindrome(s); // all words are used, then token should be null
	if (dpR[b].find(s) != dpR[b].end()) return dpR[b][s];
	ll& ref = dpR[b][s] = 0;

	if (is_palindrome(s)) ++ref;

	for (int i = 0; i < N; ++i) {
		if (b & 1 << i) continue;
		if (t[i].length() <= s.length()) {
			if (s.rfind(t[i]) == s.length() - t[i].length()) // t is suffix
				ref += fR(s.substr(0, s.length() - t[i].length()), b | 1 << i);
		}
		else {
			if (t[i].rfind(s) == t[i].length() - s.length()) { // s is suffix
				std::string r = t[i].substr(0, t[i].length() - s.length());
				std::reverse(r.begin(), r.end());
				ref += fL(r, b | 1 << i);
			}
		}
	}
	return ref;
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> t[i];
	std::cout << fL("", 0) - 1;
}