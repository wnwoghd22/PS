#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;
const int LEN = 300'001;

class LeftistHeap {
private:
	struct Node {
		ll e;
		Node* l;
		Node* r;
		int dist; // null path length
		Node(const ll& e, Node* l = 0, Node* r = 0, const int& d = 0) : e(e), l(l), r(r), dist(d) {}
		~Node() { if (l) delete l; if (r) delete r; }
		void swap_children() { Node* t = l; l = r; r = t; }
	} *root;
	Node* merge_in(Node* h1, Node* h2) {
		if (h1->l == 0) h1->l = h2;
		else {
			h1->r = merge(h1->r, h2);
			if (h1->l->dist < h1->r->dist)
				h1->swap_children();
			h1->dist = h1->r->dist + 1;
		}
		return h1;
	}
	Node* merge(Node* h1, Node* h2) {
		if (h1 == 0) return h2;
		if (h2 == 0) return h1;
		return h1->e > h2->e ? merge_in(h1, h2) : merge_in(h2, h1); // max heap
	}
	Node* clone(Node* n) {
		if (!n) return 0;
		else return new Node(n->e, clone(n->l), clone(n->r), n->dist);
	}
public:
	LeftistHeap() : root(0) {}
	LeftistHeap(LeftistHeap& r) : root(0) { *this = r; }
	~LeftistHeap() { clear(); }
	bool empty() { return root == 0; }
	void push(ll x) { root = merge(new Node(x), root); }
	ll top() { return root->e; }
	ll pop() {
		if (empty()) return -1;
		ll max = top();
		Node* old = root;
		root = merge(root->l, root->r);
		old->l = old->r = 0;
		delete old;
		return max;
	}
	void clear() { if (root) delete root; root = 0; }
	void merge(LeftistHeap& r) {
		if (this == &r) return;
		root = merge(root, r.root);
		r.root = 0;
	}
	LeftistHeap& operator=(LeftistHeap& r) {
		if (this != &r) {
			clear();
			root = clone(r.root);
		}
		return *this;
	}
} heaps[LEN];

int N, M;
ll P[LEN], C[LEN];
ll A[LEN], B[LEN]; // Ax + B

std::vector<int> graph[LEN];

void dfs(int u) {
	for (const int& v : graph[u]) {
		dfs(v);
		heaps[u].merge(heaps[v]);
		A[u] += A[v];
		B[u] += B[v];
	}
	// std::cout << "dfs " << u << '\n';
	// std::cout << "Pop while A >= 1\n";
	while (A[u] > 1) {
		// std::cout << heaps[u].top() << '\n';
		B[u] += heaps[u].top();
		A[u]--;
		heaps[u].pop();
	}
	ll a = 0;
	if (A[u] == 1) {
		a = heaps[u].top();
		B[u] += heaps[u].top();
		A[u]--;
		heaps[u].pop();
	}
	ll b = heaps[u].empty() ? 0 : heaps[u].top();
	if (!heaps[u].empty()) heaps[u].pop();
	heaps[u].push(a + C[u]);
	heaps[u].push(b + C[u]);
	A[u]++;
	B[u] -= a + C[u];
	// std::cout << A[u] << "x + " << B[u] << '\n';
}

int main() {
	std::cin >> N >> M;
	for (int i = 2; i <= N + M; ++i) {
		std::cin >> P[i] >> C[i];
		graph[P[i]].push_back(i);
	}
	dfs(1);
	while (A[1] >= 1) {
		B[1] += heaps[1].top();
		A[1]--;
		heaps[1].pop();
	}
	std::cout << B[1];
}