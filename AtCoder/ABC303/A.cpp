#include <iostream>

int N, flag = true;
char S[101], T[101];

int main() {
	std::cin >> N >> S >> T;
	for (int i = 0; i < N; ++i) {
		if (S[i] == 'l' || S[i] == '1') {
			if (T[i] == 'l' || T[i] == '1') continue;
			else {
				flag = false;
				break;
			}
		}
		else if (S[i] == 'o' || S[i] == '0') {
			if (T[i] == 'o' || T[i] == '0') continue;
			else {
				flag = false;
				break;
			}
		}
		else {
			if (S[i] != T[i]) {
				flag = false;
				break;
			}
		}
	}
	std::cout << (flag ? "Yes" : "No");
}