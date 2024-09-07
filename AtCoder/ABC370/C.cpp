#include <iostream>
#include <cstring>
#include <queue>

const int LEN = 101;

int N;
char S[LEN], T[LEN];
std::priority_queue<int> pq;

int main() {
	std::cin >> S >> T;
	N = strlen(S);
	for (int i = 0; i < N; ++i) {
		if (S[i] > T[i]) {
			pq.push(N - i);
		}
		if (S[i] < T[i]) {
			pq.push(i - N);
		}
	}
	std::cout << pq.size() << '\n';
	while (pq.size()) {
		int x = pq.top(); pq.pop();
		int i;
		if (x < 0) i = x + N;
		else if (x > 0) i = N - x;
		S[i] = T[i];
		std::cout << S << '\n';
	}
}