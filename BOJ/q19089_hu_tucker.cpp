#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>

typedef long long ll;
const int LEN = 200'001;
const ll INF = 2e17;

/// <summary>
/// reference:
/// https://www.geeksforgeeks.org/leftist-tree-leftist-heap/
/// </summary>
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
		return h1->e < h2->e ? merge_in(h1, h2) : merge_in(h2, h1);
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
		ll min = top();
		Node* old = root;
		root = merge(root->l, root->r);
		old->l = old->r = 0;
		delete old;
		return min;
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
} heaps[LEN]; // HPQ. Huffman priority queue
int N, l[LEN], r[LEN]; // working sequence
ll W[LEN], C[LEN];
struct Info {
	ll w; int i; // min_sum, position
	bool operator<(const Info& r) const { return w == r.w ? i > r.i : w > r.w; }
};
std::priority_queue<Info> pq; // MPQ. master priority queue

/// <summary>
/// reference:
/// https://sotanishy.github.io/cp-library-cpp/dp/hu_tucker.cpp
/// https://blog.myungwoo.kr/m/141
/// </summary>
/// <returns></returns>
ll hu_tucker(ll* w, int n) {
	for (int i = 0; i < LEN; ++i) heaps[i].clear();
	pq = std::priority_queue<Info>();
	ll result = 0, c, top;
	bool ml, mr;

	for (int i = 0; i < n - 1; ++i) {
		l[i] = i - 1;
		r[i] = i + 1;
		C[i] = w[i] + w[i + 1];
		pq.push({ C[i], i });
	}

	for (int k = 0, i, j; k < n - 1; ++k) {
		do {
			c = pq.top().w, i = pq.top().i;
			pq.pop();
		} while (!~r[i] || C[i] ^ c); // extract min

		ml = mr = 0;
		if (w[i] + w[r[i]] == c) ml = mr = 1; // l + r
		else {
			top = heaps[i].pop();
			if (w[i] + top == c) ml = 1; // l + m
			else if (top + w[r[i]] == c) mr = 1; // m + r
			else heaps[i].pop(); // m1 + m2
		}

		result += c;
		heaps[i].push(c);
		if (ml) w[i] = INF;
		if (mr) w[r[i]] = INF;

		if (ml && i > 0) { // l + m
			j = l[i];
			heaps[j].merge(heaps[i]);
			r[j] = r[i];
			r[i] = -1;
			l[r[j]] = j;
			i = j;
		}
		if (mr && r[i] < n - 1) { // m + r
			j = r[i];
			heaps[i].merge(heaps[j]);
			r[i] = r[j];
			r[j] = -1;
			l[r[i]] = i;
		}

		C[i] = w[i] + w[r[i]]; // l + r
		if (!heaps[i].empty()) {
			top = heaps[i].pop();
			C[i] = std::min(C[i], std::min(w[i], w[r[i]]) + top); // lm or mr
			if (!heaps[i].empty())
				C[i] = std::min(C[i], top + heaps[i].top()); // m1 + m2
			heaps[i].push(top);
		}
		pq.push({ C[i], i });
	}
	return result;
}

ll solve() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> W[i];
	return hu_tucker(W, N);
}

int main() {
	freopen("input.txt", "r", stdin);
	int T;
	std::cin >> T;
	while (T--) std::cout << solve() << '\n';
}