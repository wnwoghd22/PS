#include <iostream>

std::string reverse(const std::string& s) {
    std::string rev;
    for (int i = s.size() - 1; i >= 0; i--) {
        rev = rev.append(1, s[i]);
    };
    return rev;
}

bool check(const std::string& s) {
	int n = s.length();
	std::string p = s.substr(0, (n + 2) / 3);
	std::string t = p.substr(1);
    std::string r = reverse(p);
    std::string tr = r.substr(1);

    if (s == p + r + p) return 1;
    if (s == p + tr + p) return 1;
    if (s == p + r + t) return 1;
    if (s == p + tr + t) return 1;
    return 0;
}

int main() {
    int T;
    std::cin >> T;
    while (T--) {
        std::string s;
        std::cin >> s;
        std::cout << check(s) << '\n';
    }
}