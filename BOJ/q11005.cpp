#include <iostream>

int main() {
	int N, B;
	std::cin >> N >> B;
	char s[60];
	int len = 0;
	while (N) {
		int d = N % B;
		N /= B;
		if (d < 10) {
			s[len] = d + '0';
		}
		else {
			s[len] = d - 10 + 'A';
		}
		++len;
	}
	for (int i = len - 1; i >= 0; --i) std::cout << s[i];
}