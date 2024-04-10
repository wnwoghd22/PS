#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;
const int LEN = 1e5 + 1;

struct Pos {
    int x, y;
    bool operator<(const Pos& r) const { return x == r.x ? y > r.y : x < r.x; }
};

ll dist(const Pos& p1, const Pos& p2) { return (ll)(p1.x - p2.x) * (p1.x - p2.x) + (ll)(p1.y - p2.y) * (p1.y - p2.y); }

struct Event {
    int i, d;
    Pos p;
    bool operator<(const Event& r) const { return p < r.p; }
} events[LEN << 2];

struct Circle {
    Pos c;
    int r;
} circles[LEN << 1];

struct Arc {
    Pos c;
    int r, i;
    bool u;
    bool is_above(const Pos& p) const {
        if (u) {
            if (p.y <= c.y) return 0;
            return dist(c, p) > (ll)r * r;
        }
        if (p.y >= c.y) return 1;
        return dist(c, p) < (ll)r * r;
    }
};

int par[LEN << 1];
std::vector<int> graph[LEN << 1];

class SplayTree {
    struct Node {
        Node* l;
        Node* r;
        Node* p;
        Arc val;
        Node(int i, bool u) : l(0), r(0), p(0) { val = { circles[i].c, circles[i].r, i, u }; }
        ~Node() { if (l) delete l; if (r) delete r; }
    } *root, *ptr[LEN << 1][2];
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
public:
    SplayTree() : root(0) {}
    ~SplayTree() { if (root) delete root; }
    void insert(int i) {
        if (!root) {
            root = new Node(i, 0);
            root->r = new Node(i, 1);
            ptr[i][0] = root;
            ptr[i][1] = root->r;
            root->r->p = root;
            graph[0].push_back(i);
            return;
        }
        Node* p = root;
        Node** pp;
        while (1) {
            if (p->val.i == i) return;
            if (p->val.is_above(circles[i].c)) {
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
        ptr[i][0] = new Node(i, 0);
        ptr[i][1] = new Node(i, 1);
        ptr[i][0]->r = ptr[i][1];
        ptr[i][1]->p = ptr[i][0];
        ptr[i][0]->p = p;
        *pp = ptr[i][0];
        splay(ptr[i][1]);
        if (root->r) {
            Node* x = root->r;
            while (x->l) x = x->l;
            graph[par[i] = x->val.u ? x->val.i : par[x->val.i]].push_back(i);
        }
        else graph[0].push_back(i);
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

    void pop(int val) {
        pop(ptr[val][0]);
        pop(ptr[val][1]);
        ptr[val][0] = ptr[val][1] = 0;
    }
} sp;

int dp[LEN << 1][2];

int N, Q, ans[LEN], len;

void dfs(int u) {
    for (const int& v : graph[u]) {
        std::cout << "edge: " << u << " -> " << v << '\n';
        dfs(v);
        if (v <= Q) {
            dp[u][0] += dp[v][0];
            dp[u][1] += dp[v][1];
        }
        else {
            dp[u][0] += std::max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        }
    }
    if (u <= Q) ans[u] = std::max(dp[u][0], dp[u][1] + 1);
    else dp[u][1]++;
}

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    std::cin >> N >> Q;
    for (int i = Q + 1, x, y, r; i <= Q + N; ++i) {
        std::cin >> x >> y >> r;
        circles[i] = { { x, y }, r };
        events[len++] = { i, 1, { x - r, y } };
        events[len++] = { i, 0, { x + r, y } };
    }
    for (int i = 1, x, y, r; i <= Q; ++i) {
        std::cin >> x >> y >> r;
        circles[i] = { { x, y }, r };
        events[len++] = { i, 1, { x - r, y } };
        events[len++] = { i, 0, { x + r, y } };
    }
    std::sort(events, events + len);
    for (int i = 0; i < len; ++i) {
        if (events[i].d) sp.insert(events[i].i);
        else sp.pop(events[i].i);
    }
    dfs(0);
    for (int i = 1; i <= Q; ++i) std::cout << ans[i] << '\n';
}