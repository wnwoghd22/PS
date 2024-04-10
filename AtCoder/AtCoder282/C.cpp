#include <iostream>

const int LEN = 200'001;
char S[LEN];
int N;
bool flag;

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> S[i];
		switch (S[i]) {
		case '\"':
			flag = !flag;
			break;
		case ',':
			if (!flag) S[i] = '.';
			break;
		}
	}
	std::cout << S;
}