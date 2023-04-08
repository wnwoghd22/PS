#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>

typedef long long ll;
typedef unsigned long long ull;
class SplayTree {
    struct Node {
        Node* l;
        Node* r;
        Node* p;
        ll val;
        int key;
        int size;
        Node(ll val) : l(0), r(0), p(0), val(val), key(1), size(1) {}
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
            if (p->val == val) {
                splay(p);
                ++p->key;
                return;
            }
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
        *pp = x;
        x->p = p;
        splay(x);
    }
    int find(ll val) {
        if (!root) return 0;
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
        return p->val == val ? p->key : 0;
    }
    void pop(ll val) {
        if (!find(val)) return;
        Node* p = root;
        if (p->l && p->r) {
            root = p->l; p->l->p = 0;
            Node* l = root;
            while (l->r) l = l->r;
            l->r = p->r;
            p->r->p = l;
        }
        else if (p->l) root = p->l, root->p = 0;
        else if (p->r) root = p->r, root->p = 0;
        else root = 0;

        delete p;
    }
    ll get(int i) {
        if (!root) return -1;
        Node* p = root;
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

const int LEN = 500'000;
class HashMap {
    struct Node {
        ll val;
        int key;
        int next;
        Node() : val(0), key(1), next(-1) {}
    } nodes[LEN];
    int djb2(ll val) {
        ull key = 5381;
        while (val) {
            key = ((key << 5) + key + val) % LEN;
            val -= val & -val;
        }
        return key;
    }
    int bucket[LEN];
    int size;
public:
    HashMap() { size = 0; memset(bucket, -1, sizeof bucket); }
    void insert(ll val) {
        int key = djb2(val);
        if (!~bucket[key]) {
            bucket[key] = size;
            nodes[size].val = val;
            ++size;
            return;
        }
        int cur = bucket[key];
        while (1) {
            if (nodes[cur].val == val) {
                ++nodes[cur].key;
                return;
            }
            if (!~nodes[cur].next) break;
            cur = nodes[cur].next;
        }
        nodes[cur].next = size;
        nodes[++size].val = val;
    }
    int find(ll val) {
        int key = djb2(val);
        if (!~bucket[key]) return 0;
        int cur = bucket[key];
        while (1) {
            if (nodes[cur].val == val) return nodes[cur].key;
            if (!~nodes[cur].next) break;
            cur = nodes[cur].next;
        }
        return 0;
    }
} map;

int main() {
    int N, M, A;
    scanf("%d", &N);
    while (N--) {
        scanf("%d", &A);
        // sp.insert(A);
        map.insert(A);
    }
    scanf("%d", &M);
    while (M--) {
        scanf("%d", &A);
        // printf("%d ", sp.find(A));
        printf("%d ", map.find(A));
    }
}