#include <iostream>

typedef long long ll;
char S[61];
ll N, len, result, i;

int main() {
	std::cin >> S >> N;
	for (len = 0; S[len]; ++len);
	for (result = 0, i = 0; i < len; ++i)
		if (S[i] == '1') result += 1ll << (len - i - 1);
	
	if (result > N) result = -1;
	else {
		for (i = 0; i < len; ++i) {
			if (S[i] == '?') {
				ll cur = 1ll << len - i - 1;
				if (result + cur <= N)
					result += cur;
			}
		}
	}
	std::cout << result;
}
