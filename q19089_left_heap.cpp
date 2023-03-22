typedef long long ll;

// leftist heap
class LeftistHeap {
	struct Node {
		ll e;
		Node* l;
		Node* r;
		int dist;
		Node(const int& e, Node* l = 0, Node* r = 0, const int& d = 0) : e(e), l(l), r(r), dist(d) {}
	} *root;


};