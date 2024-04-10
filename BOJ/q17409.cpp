#include <iostream>
#include <vector>

typedef long long int ll;

class SegTree {
private:
	static const ll MOD = 1e9 + 7;
	int end;
	std::vector<ll> V;
	void update_diff(int n, ll diff, int index, int start, int end) {
		if (n > end || n < start) return;
		V[index] = (V[index] + diff) % MOD;

		if (start == end) return;
		int mid = (start + end) / 2;
		update_diff(n, diff, index * 2, start, mid);
		update_diff(n, diff, index * 2 + 1, mid + 1, end);
	}
	ll get_sum(int left, int right, int index, int start, int end) {
		if (left > end || right < start) return 0;
		if (left <= start && end <= right) return V[index];
		int mid = (start + end) / 2;
		return (get_sum(left, right, index * 2, start, mid) + get_sum(left, right, index * 2 + 1, mid + 1, end)) % MOD;
	}
public:
	SegTree(int n) : end(n), V(n * 4, 0) {}
	void update_diff(int n, ll diff) { update_diff(n, diff, 1, 0, end); }
	ll get_sum(int left = 0, int right = MOD) { return get_sum(left, right, 1, 0, end); }
} *dp[11];
int N, K, A;

int main() { // O(KNlogN)
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> K;
	for (int i = 0; i <= K; ++i) dp[i] = new SegTree(N);
	while (N--) {
		std::cin >> A;
		for (int i = 1; i <= K; ++i) {
			int sum = i - 1 ? dp[i - 1]->get_sum(0, A - 1) : 1;
			dp[i]->update_diff(A, sum);
		}
	}
	std::cout << dp[K]->get_sum();
}