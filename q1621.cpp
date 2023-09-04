#include <iostream>

typedef long long ll;
const int LEN = 1e6 + 1;

int N, K, C;
int A[LEN];
ll cost[LEN];
int k[LEN];
int sp, trace[LEN];

int main() {
	std::cin >> N >> K >> C;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];

	for (int i = 1; i < K; ++i) cost[i] = A[i] + cost[i - 1];
	for (int i = K; i <= N; ++i) {
		ll c = cost[i - K] + C;
		ll a = cost[i - 1] + A[i];
		if (c < a) {
			k[i] = k[i - K] + 1;
			cost[i] = c;
		}
		else {
			k[i] = k[i - 1];
			cost[i] = a;
		}
	}
	std::cout << cost[N] << '\n';
	std::cout << k[N] << '\n';

	int remain = k[N];
	for (int i = N; i >= K; --i) {
		if (k[i] == remain && cost[i - K] + C == cost[i]) {
			trace[sp++] = i - K + 1;
			--remain;
		}
	}
	while (sp) std::cout << trace[--sp] << ' ';
}