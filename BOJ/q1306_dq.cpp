#include <iostream>
#include <algorithm>
#include <deque>

const int LEN = 1e6;

int N, M, A[LEN];
struct E { int x, i; };
std::deque<E> dq;
void push(int x, int i) {
	while (dq.size() && dq.back().x <= x) dq.pop_back();
	dq.push_back({ x, i });
}
int get_max(int i) {
	while (dq.size() && dq.front().i < i - M * 2 + 2) dq.pop_front();
	return dq.front().x;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	for (int i = 0; i < M * 2 - 2; ++i) push(A[i], i);
	for (int i = M * 2 - 2; i < N; ++i) {
		push(A[i], i);
		std::cout << get_max(i) << ' ';
	}
}