#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>

const int LEN = 1e6 + 1;

class SplayTree {
public:
    struct Node {
        Node* l;
        Node* r;
        Node* p;
        int val;
        int size;
        Node(int val) : l(0), r(0), p(0), val(val), size(1) {}
        ~Node() {
            std::cout << "delete " << val << '\n';
            if (l) delete l; 
            if (r) delete r; 
        }
        void update() {
            size = 1;
            if (l) size += l->size;
            if (r) size += r->size;
        }
    } *root;
    void rotate(Node* x) {
        Node* p = x->p;
        if (!p) return;
        Node* b = 0;
        if (x == p->l) {
            p->l = b = x->r;
            x->r = p;
        }
        else {
            p->r = b = x->l;
            x->l = p;
        }
        x->p = p->p;
        p->p = x;
        if (b) b->p = p;
        (x->p ? p == x->p->l ? x->p->l : x->p->r : root) = x;
        p->update();
        x->update();
    }
    void splay(Node* x) {
        while (x->p) {
            Node* p = x->p;
            Node* g = p->p;
            if (g) {
                if ((x == p->l) == (p == g->l)) rotate(p);
                else rotate(x);
            }
            rotate(x);
        }
    }
    SplayTree() : root(0) {}
    ~SplayTree() { if (root) delete root; }
    int size() { return root ? root->size : 0; }
    void insert(int val) {
        if (!root) {
            root = new Node(val);
            return;
        }
        Node* p = root;
        Node** pp;
        while (1) {
            if (p->val == val) return;
            if (p->val > val) {
                if (!p->l) {
                    pp = &p->l;
                    break;
                }
                p = p->l;
            }
            else {
                if (!p->r) {
                    pp = &p->r;
                    break;
                }
                p = p->r;
            }
        }
        Node* x = new Node(val);
        x->p = p;
        *pp = x;
        splay(x);
    }
    bool find(int val) {
        if (!root) return false;
        Node* p = root;
        while (1) {
            if (p->val == val) break;
            if (p->val > val) {
                if (!p->l) break;
                p = p->l;
            }
            else {
                if (!p->r) break;
                p = p->r;
            }
        }
        splay(p);
        return p->val == val;
    }
    void pop(int val) {
        if (!find(val)) return;
        Node* p = root;
        std::cout << "pop " << val << '\n';

        if (p->l && p->r) {
            std::cout << "l and r\n";
            root = p->l; root->p = 0;
            Node* l = root;
            while (l->r) l = l->r;
            l->r = p->r;
            p->r->p = l;
            l->update();
            splay(l);
        }
        else if (p->l) root = p->l, root->p = 0;
        else if (p->r) root = p->r, root->p = 0;
        else root = 0;
        p->l = 0;
        p->r = 0;

        std::cout << "delete\n";
        delete p;
        p = 0;
    }
    int get(int i) {
        Node* p = root;
        if (!p) return -1;
        while (1) {
            while (p->l && p->l->size > i) p = p->l;
            if (p->l) i -= p->l->size;
            if (!i--) break;
            p = p->r;
        }
        splay(p);
        return p->val;
    }
} st[LEN];

int N, M, A[LEN];

struct SegMax {
	int seg_max[LEN << 2];
	void update(int x, int d, int s = 1, int e = N, int i = 1) {
		if (x < s || e < x) return;
		if (s == e) { seg_max[i] = d; return; }
		int m = s + e >> 1;
		update(x, d, s, m, i << 1);
		update(x, d, m + 1, e, i << 1 | 1);
		seg_max[i] = std::max(seg_max[i << 1], seg_max[i << 1 | 1]);
	}
	int get_max(int l, int r, int s = 1, int e = N, int i = 1) {
		if (r < s || e < l) return 0;
		if (l <= s && e <= r) { return seg_max[i]; }
		int m = s + e >> 1;
		return std::max(get_max(l, r, s, m, i << 1), get_max(l, r, m + 1, e, i << 1 | 1));
	}
} depth, signals;

int get_rightmost(int i) {
	int l = i + 1, r = N, m, j = N + 1;
	while (l <= r) {
		m = l + r >> 1;
        if (depth.get_max(i + 1, m) > A[i]) {
			j = std::min(m, j);
			r = m - 1;
		}
		else l = m + 1;
	}
	return j;
}

std::stack<int> s;

int main() {
    // freopen("input.txt", "r", stdin);
    freopen("submarines.18.in", "r", stdin);
    freopen("output.txt", "w", stdout);
    // std::cin.tie(0)->sync_with_stdio(0);
    std::cin >> N >> M;
    for (int i = 1; i <= N; ++i) {
        std::cin >> A[i], depth.update(i, A[i]);
        // if (A[i] > A[i - 1])
        //    std::cout << i << ", " << A[i] << ", " << A[i - 1] << '\n';
    }
    for (int i = N; i; --i) {
        while (s.size() && A[s.top()] <= A[i]) s.pop();
        if (s.size()) st[s.top()].insert(A[i]);
        s.push(i);
    }
    for (int i = 1; i <= N; ++i) signals.update(i, st[i].size());

    // for (int i = 1; i <= N; ++i)
    //    std::cout << st[i].size() << ' ';

    for (int m = 0, i; m < M; ++m) {
        std::cin >> i;
        if (i) {
            std::cout << "swap " << i << ": " << A[i] << ", " << A[i + 1] << '\n';
            if (A[i] < A[i + 1]) {
                st[i + 1].pop(A[i]);
                if (st[i + 1].root) { // merge splay trees
                    if (st[i].root) {
                        st[i].find(A[i]); // splay biggest
                        st[i].root->r = st[i + 1].root;
                        st[i + 1].root->p = st[i].root;
                        st[i].root->update();
                    }
                    else st[i].root = st[i + 1].root;
                    st[i + 1].root = 0;
                }
                signals.update(i, st[i].size());
                signals.update(i + 1, st[i + 1].size());
                std::swap(A[i], A[i + 1]);
                depth.update(i, A[i]);
                depth.update(i + 1, A[i + 1]);
                int r = get_rightmost(i + 1);
                std::cout << "r " << i + 1 << ": " << A[i + 1] << ", " << A[r] << '\n';
                if (r <= N) {
                    st[r].insert(A[i + 1]);
                    signals.update(r, st[r].size());
                }
            }
            else { // A[i] > A[i + 1]
                int r = get_rightmost(i + 1);
                std::cout << "r " << i + 1 << ": " << A[i + 1] << ", " << r << ' ' <<  A[r] << '\n';
                if (r <= N) {
                    std::cout << "pop " << A[i + 1] << '\n';
                    st[r].pop(A[i + 1]);
                    signals.update(r, st[r].size());
                }
                st[i].insert(A[i + 1]); // insert A[i + 1] and splay
                st[i + 1].root = st[i].root;
                st[i].root = st[i + 1].root->l; // separate set strictly smaller than A[i + 1]
                st[i + 1].root->l = 0;
                st[i + 1].root->update();
                if (st[i].root)
                    st[i].root->p = 0;
                signals.update(i, st[i].size());
                signals.update(i + 1, st[i + 1].size());
                std::swap(A[i], A[i + 1]);
                depth.update(i, A[i]);
                depth.update(i + 1, A[i + 1]);
            }
        }
        else std::cout << signals.get_max(1, N) << '\n';
    }
}