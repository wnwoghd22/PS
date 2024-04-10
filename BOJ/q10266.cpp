#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

const int LEN = 200'000;
int N;
int t[LEN * 2], p[LEN], fail[LEN];
bool cnt[360'000];

void sort(int n, int* a) {
	for (int i = 0; i < n; ++i) cnt[a[i]] = 1;
	for (int i = 0, j = 0; j < n; ++i) if (cnt[i]) a[j++] = i;
}

int kmp() {
	for (int i = 1, j = 0; i < N - 1; ++i) {
		while (j && p[i] ^ p[j]) j = fail[j - 1];
		if (p[i] == p[j]) fail[i] = ++j;
	}
	int result = 0;
	for (int i = 0, j = 0; i < N * 2 - 1; ++i) {
		while (j && t[i] ^ p[j]) j = fail[j - 1];
		if (t[i] == p[j]) {
			if (j == N - 2) {
				++result;
				j = fail[j];
			}
			else ++j;
		}
	}
	return result;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> t[i];
	for (int i = 0; i < N; ++i) std::cin >> p[i];
	sort(N, t); sort(N, p);
	for (int i = 0; i < N; ++i) t[N + i] = t[i];
	for (int i = 0; i < N - 1; ++i) p[i] = p[i + 1] - p[i];
	for (int i = 0; i < N * 2 - 1; ++i) {
		t[i] = t[i + 1] - t[i];
		if (t[i] < 0) t[i] += 360'000;
	}
	std::cout << (kmp() ? "possible" : "impossible");
}
