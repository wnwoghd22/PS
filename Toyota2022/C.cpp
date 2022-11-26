#include <iostream>
#include <cstring>

const int LEN = 400'001;
int H, W, C[LEN], Cs[LEN], Ls[LEN], Ct[LEN], Lt[LEN];

int main() {
	std::string S, T;
	std::cin >> H >> W;
	for (int i = 0, c = 0; i < H; ++i) {
		std::cin >> S;
		for (int j = 0; j < W; ++j)
			if (S[j] == '#') ++C[j], ++c;
		Ls[i] = c;
	}
	for (int i = 0; i < W; ++i) Cs[C[i]]++;

	memset(C, 0, sizeof C);

	for (int i = 0, c = 0; i < H; ++i) {
		std::cin >> T;
		for (int j = 0; j < W; ++j)
			if (T[j] == '#') ++C[j], ++c;
		Lt[i] = c;
	}
	for (int i = 0; i < W; ++i) Ct[C[i]]++;

	bool flag = true;

	for (int i = 0; i < H; ++i) if (Ls[i] != Lt[i]) flag = false;
	for (int i = 0; i <= H; ++i) if (Cs[i] != Ct[i]) flag = false;

	std::cout << (flag ? "Yes" : "No");
}