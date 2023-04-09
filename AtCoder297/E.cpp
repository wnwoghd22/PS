#include <iostream>

typedef long long ll;
const int LEN = 2e5 + 1;
class SplayTree {
    struct Node {
        Node* l;
        Node* r;
        Node* p;
        ll val;
        int size;
        Node(ll val) : l(0), r(0), p(0), val(val), size(1) {}
        ~Node() { if (l) delete l; if (r) delete r; }
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
public:
    SplayTree() : root(0) {}
    ~SplayTree() { if (root) delete root; }
    void insert(ll val) {
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
    bool find(ll val) {
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
    void pop(ll val) {
        if (!find(val)) return;
        Node* p = root;
        
        if (p->l && p->r) {
            root = p->l; root->p = 0;
            Node* l = root;
            while (l->r) l = l->r;
            l->r = p->r;
            p->r->p = l;
        }
        else if (p->l) root = p->l, root->p = 0;
        else if (p->r) root = p->r, root->p = 0;
        else root = 0;
        p->l = p->r = 0;
        delete p;
    }
    ll get(int i) {
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
} sp;
ll N, K, A[10], ans[LEN];

int main() {
    std::cin >> N >> K;
    for (int i = 0; i < N; ++i) std::cin >> A[i];
    sp.insert(0);
    for (int i = 0; i <= K; ++i) {
        ll min = sp.get(0);
        sp.pop(min);
        for (int j = 0; j < N; ++j) {
            sp.insert(min + A[j]);
        }
        ans[i] = min;
    }
    std::cout << ans[K];
}