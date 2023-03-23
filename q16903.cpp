#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

const int BIT = 32;

class Trie {
	struct Node {
		Node* child[2];
		int cnt;
		Node() : cnt(0) { child[0] = child[1] = 0; }

		void insert(int n, int d) {
			++cnt;
			if (d == BIT) return;
			int next = !!(n & 1 << (BIT - d - 1));
			// std::cout << n << ' ' << d << ' ' << next << "count: " << cnt << '\n';
			if (!child[next]) child[next] = new Node;
			child[next]->insert(n, d + 1);
		}
		int remove(int n, int d) {
			if (d < BIT) {
				int next = !!(n & 1 << (BIT - d - 1));
				if (child[next] && !child[next]->remove(n, d + 1)) {
					// std::cout << "delete: " << n << ' ' << d << '\n';
					delete child[next];
					child[next] = 0;
				}
			}
			return --cnt;
		}
		int find_biggest(int x, int d, int v) {
			if (d == BIT) return v;
			int next = !(x & 1 << (BIT - d - 1)); // XOR
			// std::cout << x << ' ' << d << ' ' << next << '\n';
			if (child[next])
				return child[next]->find_biggest(x, d + 1, v << 1 | 1);
			return child[!next]->find_biggest(x, d + 1, v << 1);
		}
	} *root;
public:
	Trie() { root = new Node; }
	void insert(int n) { root->insert(n, 0); }
	void remove(int n) { root->remove(n, 0); }
	int find_biggest(int x) { return root->find_biggest(x, 0, 0); }
};

int M, Q, X;

int main() {
	freopen("input.txt", "r", stdin);
	Trie A;
	A.insert(0);
	std::cin >> M;
	while (M--) {
		std::cin >> Q >> X;
		// std::cout << "Query: " << Q << ' ' << X << '\n';
		if (Q == 1) A.insert(X);
		if (Q == 2) A.remove(X);
		if (Q == 3) std::cout << A.find_biggest(X) << '\n';
	}
}