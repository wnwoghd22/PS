#include <iostream>
#include <map>

typedef long long ll;
const ll MOD = 835454957;

int N, K;
std::string t[50];
std::map<std::string, ll> dpL[101];
std::map<std::string, ll> dpR[101];

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

ll fL(std::string s, int k) {
	if (k <= 0) return is_palindrome(s); // all words are used, then token should be null
	if (dpL[k].find(s) != dpL[k].end()) return dpL[k][s];
	ll& ref = dpL[k][s] = 0;

	if (is_palindrome(s)) ++ref;

	for (int i = 0; i < N; ++i) {
		if (t[i].length() > k) continue;

		if (t[i].length() <= s.length()) {
			if (s.rfind(t[i], 0) == 0) { // if t is prefix
				ref += fL(s.substr(t[i].length()), k - t[i].length() - 1);
				ref %= MOD;
			}
		}
		else {
			if (t[i].rfind(s, 0) == 0) { // if s is prefix
				std::string r = t[i].substr(s.length());
				std::reverse(r.begin(), r.end());
				ref += fR(r, k - t[i].length() - 1);
				ref %= MOD;
			}
		}
	}
	return ref;
}

ll fR(std::string s, int k) {
	if (k <= 0) return is_palindrome(s); // all words are used, then token should be null
	if (dpR[k].find(s) != dpR[k].end()) return dpR[k][s];
	ll& ref = dpR[k][s] = 0;

	if (is_palindrome(s)) ++ref;

	for (int i = 0; i < N; ++i) {
		if (t[i].length() > k) continue;

		if (t[i].length() <= s.length()) {
			if (s.rfind(t[i]) == s.length() - t[i].length()) { // t is suffix
				ref += fR(s.substr(0, s.length() - t[i].length()), k - t[i].length() - 1);
				ref %= MOD;
			}
		}
		else {
			if (t[i].rfind(s) == t[i].length() - s.length()) { // s is suffix
				std::string r = t[i].substr(0, t[i].length() - s.length());
				std::reverse(r.begin(), r.end());
				ref += fL(r, k - t[i].length() - 1);
				ref %= MOD;
			}
		}
	}
	return ref;
}

int main() {
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i) std::cin >> t[i];
	std::cout << fL("", K) - 1;
}