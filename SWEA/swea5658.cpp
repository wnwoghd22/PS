#include <iostream>
#include <algorithm>

char str[29];
int N, K, arr[28], sp;

int get_i(char c) {
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return c - '0';
}

struct Node { // Trie
    Node* child[16];
    int flag;
    Node() : flag(0) { for (int i = 0; i < 16; ++i) child[i] = 0; }
    ~Node() {
        for (int i = 0; i < 16; ++i)
            if (child[i])
                delete child[i];
    }
    void insert(int i, int d, int s) {
        if (d == N / 4) {
            if (!flag) {
                // std::cout << "insert " << s << '\n';
                flag = true;
                arr[sp++] = s;
            }
            return;
        }
        int cur = get_i(str[i]);
        // std::cout << "depth: " << d << ", cur: " << cur << '\n';
        int next = (i + 1) % N;
        if (!child[cur]) child[cur] = new Node;
        child[cur]->insert(next, d + 1, s * 16 + cur);
    }
};

int solve() {
    std::cin >> N >> K >> str;
    Node trie;
    sp = 0;
    for (int i = 0; i < N; ++i) trie.insert(i, 0, 0);
    std::sort(arr, arr + sp);
    return arr[sp - K];
}

int main() {
    int t, T;
    std::cin >> T;
    for (t = 1; t <= T; ++t) std::cout << '#' << t << ' ' << solve() << '\n';
}