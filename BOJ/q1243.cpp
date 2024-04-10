#include <iostream>
#include <string>
#include <map>

typedef long long ll;

int N, L;
std::string t[50];
std::map<std::string, ll> dpL[31];
std::map<std::string, ll> dpR[31];

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

ll fL(std::string s, int l) {
	if (l == L) return is_palindrome(s); // all words are used, then token should be null
	if (dpL[l].find(s) != dpL[l].end()) return dpL[l][s];
	ll& ref = dpL[l][s] = 0;

	// if (is_palindrome(s)) ++ref;

	for (int i = 0; i < N; ++i) {
		if (l + t[i].length() > L) continue;

		if (t[i].length() <= s.length()) {
			if (s.rfind(t[i], 0) == 0) // if t is prefix
				ref += fL(s.substr(t[i].length()), l + t[i].length());
		}
		else {
			if (t[i].rfind(s, 0) == 0) { // if s is prefix
				std::string r = t[i].substr(s.length());
				std::reverse(r.begin(), r.end());
				ref += fR(r, l + t[i].length());
			}
		}
	}
	return ref;
}

ll fR(std::string s, int l) {
	if (l == L) return is_palindrome(s); // all words are used, then token should be null
	if (dpR[l].find(s) != dpR[l].end()) return dpR[l][s];
	ll& ref = dpR[l][s] = 0;

	// if (is_palindrome(s)) ++ref;

	for (int i = 0; i < N; ++i) {
		if (l + t[i].length() > L) continue;

		if (t[i].length() <= s.length()) {
			if (s.rfind(t[i]) == s.length() - t[i].length()) // t is suffix
				ref += fR(s.substr(0, s.length() - t[i].length()), l + t[i].length());
		}
		else {
			if (t[i].rfind(s) == t[i].length() - s.length()) { // s is suffix
				std::string r = t[i].substr(0, t[i].length() - s.length());
				std::reverse(r.begin(), r.end());
				ref += fL(r, l + t[i].length());
			}
		}
	}
	return ref;
}

int main() {
	std::cin >> N >> L;
	for (int i = 0; i < N; ++i) std::cin >> t[i];
	std::cout << fL("", 0);
}