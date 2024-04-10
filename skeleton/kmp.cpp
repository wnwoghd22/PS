#include <string>

const int LEN = 201;
int fail[LEN];

int kmp(const std::string& p, const std::string& t) {
	memset(fail, 0, sizeof fail);
	for (int i = 1, j = 0; i < p.length(); ++i) {
		while (j && p[j] != p[i]) j = fail[j - 1];
		if (p[j] == p[i]) fail[i] = ++j;
	}
	int result = 0;
	for (int i = 0, j = 0; i < t.length() - 1; ++i) {
		while (j && t[i] != p[j]) j = fail[j - 1];
		if (t[i] == p[j]) {
			if (j == p.length() - 1) {
				++result;
				j = fail[j];
			}
			else ++j;
		}
	}
	return result;
}