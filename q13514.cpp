#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

const int LEN = 100'001;
const int INF = 1e9 + 7;
class SplayTree {
    struct Node {
        Node* l;
        Node* r;
        Node* p;
        int val;
        int size;
        int count;
        Node(int val) : l(0), r(0), p(0), val(val), size(1), count(1) {}
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
    int size() { return root ? root->size : 0; }
    void insert(int val) {
        if (!root) {
            root = new Node(val);
            return;
        }
        Node* p = root;
        Node** pp;
        while (1) {
            if (p->val == val) {
                ++p->count;
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
        if (--p->count) return;

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
} sp[LEN];

std::vector<int> tree[LEN];
std::vector<int> cent_tree[LEN];

int N, M, size[LEN];
bool visited[LEN];

void add_edge(int u, int v) {
	tree[u].push_back(v);
	tree[v].push_back(u);
}

int get_size(int u, int p = 0) {
	size[u] = 1;
	for (const int& v : tree[u]) {
		if (v == p || visited[v]) continue;
		size[u] += get_size(v, u);
	}
	return size[u];
}

int get_cent(int u, int p, int s) {
	for (const int& v : tree[u]) {
		if (v != p && !visited[v] && size[v] * 2 > s)
			return get_cent(v, u, s);
	}
	return u;
}

int decompose_tree(int u) {
	int cent = get_cent(u, 0, get_size(u));
	// std::cout << u << ' ' << size[u] << ' ' << cent << '\n';
	visited[cent] = 1;
	for (const int& v : tree[cent]) {
		if (!visited[v]) {
			int sub_cent = decompose_tree(v);
			cent_tree[cent].push_back(sub_cent);
			cent_tree[sub_cent].push_back(cent);
		}
	}
	return cent;
}

int level[LEN], parent[LEN][21];
void dfs(int u, int p = 0) {
    parent[u][0] = p;
    level[u] = level[p] + 1;
    for (int i = 1, v = p; v; v = parent[u][i++]) {
        parent[u][i] = parent[v][i - 1];
    }
    for (const int& v : tree[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
}
int lca(int u, int v) {
    if (level[u] ^ level[v]) {
        if (level[u] > level[v]) std::swap(u, v);
        for (int i = 20; i >= 0; --i)
            if (level[parent[v][i]] >= level[u])
                v = parent[v][i];
    }
    int l = u;
    if (u ^ v) {
        for (int i = 20; i >= 0; --i) {
            if (parent[u][i] ^ parent[v][i]) {
                u = parent[u][i];
                v = parent[v][i];
            }
            l = parent[u][i];
        }
    }
    return l;
}
int dist(int u, int v) { return level[u] + level[v] - level[(lca(u, v))] * 2; }

int cent_parent[LEN], white[LEN];
void dfs_cent(int u, int p = 0) {
	cent_parent[u] = p;
	for (const int& v : cent_tree[u])
		if (v != p)
			dfs_cent(v, u);
}
void toggle(int u) {
    int v = u;
    white[u] ^= 1;
    while (v) {
        int d = dist(u, v);
        white[u] ? sp[v].insert(d) : sp[v].pop(d);
        v = cent_parent[v];
    }
}
int query(int u) {
    int v = u, min = INF;
    while (v) {
        int d = dist(u, v);
        if (sp[v].size()) min = std::min(min, sp[v].get(0) + d);
        v = cent_parent[v];
    }
    return min == INF ? -1 : min;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		add_edge(u, v);
	}
    dfs(1);

	int root = decompose_tree(1);
	dfs_cent(root);

    std::cin >> M;
    for (int i = 0, q, u; i < M; ++i) {
        std::cin >> q >> u;
        if (q == 1) toggle(u);
        if (q == 2) std::cout << query(u) << '\n';
    }
}