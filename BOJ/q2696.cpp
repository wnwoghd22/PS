#include <iostream>
#include <queue>

int T, N;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	while (T--) {
		std::priority_queue<int> ql, qr;
		std::cin >> N;
		std::cout << (N + 1) / 2 << '\n';
		for (int i = 0, a; i < N; ++i) {
			std::cin >> a;
			if (ql.empty()) ql.push(a);
			else if (a <= ql.top()) ql.push(a);
			else qr.push(-a);

			if (~i & 1) {
				while (ql.size() > qr.size() + 1) {
					qr.push(-ql.top()); ql.pop();
				}
				while (ql.size() < qr.size() + 1) {
					ql.push(-qr.top()); qr.pop();
				}
				while (ql.size() && qr.size() && ql.top() > -qr.top()) {
					a = ql.top(); 
					ql.pop(); ql.push(-qr.top());
					qr.pop(); qr.push(-a);
				}
				std::cout << ql.top() << '\n';
			}
		}
	}
}