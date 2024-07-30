#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

#define JAY_MODULE_DEBUG

typedef long long ll;
const int LEN = 1e5 + 1;

int N;
std::vector<int> g[LEN]; // above lines
struct Pos { int x, y; } pos[LEN];

void match(int u, int v, int l, int r) {
#ifdef JAY_MODULE_DEBUG
    std::cout << "facing pair: " << u << ' ' << v << '\n';
    std::cout << "    facing range: " << l << ' ' << r << '\n';
#endif
    g[u].push_back(v);
}

ll dist(const Pos& p1, const Pos& p2) { return (ll)(p1.x - p2.x) * (p1.x - p2.x) + (ll)(p1.y - p2.y) * (p1.y - p2.y); }

struct Line {
    int y;      // y coord
    int l, r;   // x coords (l <= r)

    /// <summary>
    /// sort lines
    /// 1. compare y.
    /// 2. if y coords are equal, compare x.
    /// </summary>
    /// <param name="o">other</param>
    /// <returns></returns>
    bool operator<(const Line& o) const {
        return y == o.y ? l < o.l : y > o.y;
    }
};

int Q;

/// <summary>
/// event horizon
/// </summary>
struct Event {
    int i; // index of event line
    int d; // flag value. (0: insert range, 1: query range)
    Line l; // line
    bool operator<(const Event& r) const { return l < r.l; }
} events[LEN];

/// <summary>
/// segment struct defined to use in SplayTree node.
/// simplified version of line event (ommited y coord)
/// </summary>
struct Seg {
    int l, r; // x coords
    int i;

    /// <summary>
    /// only compare x coords
    /// </summary>
    /// <param name="o">other</param>
    /// <returns></returns>
    bool operator<(const Seg& o) const {
        return l < o.l;
    }
};

class SplayTree {
    struct Node {
        Node* l;
        Node* r;
        Node* p;
        Seg val;
        Node(int l, int r, int i) : l(0), r(0), p(0) { val = { l, r, i }; }
        ~Node() { if (l) delete l; if (r) delete r; }
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

    /// <summary>
    /// find a line that has nearest r coord from l.  
    /// </summary>
    /// <param name="l">: target x coord</param>
    /// <returns></returns>
    Node* find(int l) {
        if (!root) return 0;

        Node* p = root;
        while (1) {
            if (p->val.r == l) break;
            if (p->val.r < l) {
                if (!p->r) {
                    break;
                }
                p = p->r;
            }
            else {
                if (!p->l) {
                    break;
                }
                p = p->l;
            }
        }
        splay(p);
        return p;
    }

public:
    SplayTree() : root(0) {}
    ~SplayTree() { if (root) delete root; }
    void insert(int l, int r, int i) {
        if (!root) {
            root = new Node(l, r, i);
            return;
        }
        Node* p = root;
        Node** pp;
        while (1) {
            if (p->val.l < l) {
                if (!p->r) {
                    pp = &p->r;
                    break;
                }
                p = p->r;
            }
            else {
                if (!p->l) {
                    pp = &p->l;
                    break;
                }
                p = p->l;
            }
        }
        Node* x = new Node(l, r, i);
        *pp = x;
        x->p = p;
        splay(x);
    }
    void pop(Node* ptr) {
        if (!ptr) return;
        splay(ptr);
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

    /// <summary>
    /// find leftmost line first.
    /// if line is splitted by query segment, then insert new segment and return.
    /// else, find right segments while r coord of segment is smaller than query r.
    /// </summary>
    /// <param name="l">x coord</param>
    /// <param name="r">x coord</param>
    /// <param name="i">line index</param>
    void query(int l, int r, int i) {
        assert(root);

        Node* x = find(l); // first segment
        assert(x->val.l <= l);

        if (x->val.r < l) { // if segment is out of range: find very right one
            x = x->r;
            while (x->l) x = x->l;
        }

        if (x->val.r > r) { // if splitted
            match(i, x->val.i, l, r);
            int nl = r, nr = x->val.r, ni = x->val.i;
            x->val.r = l; // split
            if (x->val.l == l) pop(x); // and pop if left is covered.
            insert(nl, nr, ni); // insert new right segment
            return;
        }

        match(i, x->val.i, l, x->val.r); // match two of them
        x->val.r = l; // left side of segment is covered by query segment
        if (x->val.r == x->val.l) pop(x); // pop if all range covered

        while (x = find(l)) { // find leftmost
            if (x->val.r == l) {
                if (!x->r) return; // no more right segment
                x = x->r;
                while (x->l) x = x->l; // find very right segment
            }
            match(i, x->val.i, x->val.l, std::min(r, x->val.r)); // match two of them
            if (x->val.r > r) { // if right segment is not covered totally
                x->val.l = r;
                break; // then, query range is sweeped. return
            }
            else pop(x); // else, a segment is sweeped. pop and find next segment
        }
    }
} sp;

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    std::cin >> N;
    for (int i = 0; i < N; ++i) std::cin >> pos[i].x >> pos[i].y;

    // horizontal check
    Q = 0;
    for (int i = 0; i < N; ++i) {
        int j = (i + 1) % N;
        if (pos[i].y == pos[j].y) {
            if (pos[i].x < pos[j].x) { // right halfline
                events[Q++] = { i, 1, { pos[i].y, pos[i].x, pos[j].x } };
            }
            if (pos[i].x > pos[j].x) { // left halfline
                events[Q++] = { i, 0, { pos[i].y, pos[j].x, pos[i].x } };
            }
        }
    }

    std::sort(events, events + Q);
    for (int i = 0; i < Q; ++i) {
        std::cout << (events[i].d == 0 ? "insert" : "query") << " segment: (h, l, r) ";
        std::cout << events[i].l.y << ' ' << events[i].l.l << ' ' << events[i].l.r << '\n';
        if (events[i].d == 0) sp.insert(events[i].l.l, events[i].l.r, events[i].i);
        if (events[i].d == 1) sp.query(events[i].l.l, events[i].l.r, events[i].i);
    }

    for (int i = 0; i <= N; ++i) {
        if (g[i].size()) {
            std::cout << "right half-line from " << i << '\n';
            std::cout << "    matching left half-lines from: ";
            for (const int& j : g[i]) std::cout << j << ' ';
            std::cout << '\n';
        }
    }
}