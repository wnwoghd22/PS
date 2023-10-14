#include <iostream>

typedef long long ll;
int N, R, C;
ll M;

int main() {
	std::cin >> N >> R >> C;
	for (int i = 0; i < N; ++i) {
		M |= ((R & 1) << 1 | C & 1) << i * 2;
		R >>= 1, C >>= 1;
	}
	std::cout << M;
}