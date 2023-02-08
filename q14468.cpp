#include <iostream>

const int LEN = 100'000;
const int INF = 2e9;

struct Node {
  int i, v;
  Node() : i(0), v(INF) {}
  Node(int i, int v) : i(i), v(v) {}
  Node operator|(const Node& r) {
    Node result;
    if (r.v < v) result.v = r.v, result.i = r.i;
    else result.v = v, result.i = i;
    return result;
  }
} seg_tree[LEN];
int N, M, q, i, j, v;

void update(int i, int v, int s = 1, int e = N, int idx = 1) {
  if (e < i || i < s) return;
  if (s == e) {
    seg_tree[idx] = Node(i, v);
    return;
  }
  int mid = (s + e) / 2;
  update(i, v, s, mid, idx << 1);
  update(i, v, mid + 1, e, idx << 1 | 1);
  seg_tree[idx] = seg_tree[idx << 1] | seg_tree[idx << 1 | 1];
}

Node get(const int l, const int r, int s = 1, int e = N, int idx = 1) {
  if (e < l || r < s) return Node(0, INF);
  if (l <= s && e <= r) return seg_tree[idx];
    
  int mid = (s + e) / 2;
  return get(l, r, s, mid, idx << 1) | get(l, r, mid + 1, e, idx << 1 | 1);
}

int main() {
  std::cin >> N;
  for (i = 1; i <= N; ++i) {
    std::cin >> v;
    update(i, v);
  }
  std::cin >> M;
  while (M--) {
    std::cin >> q;
    if (q == 1) {
      std::cin >> i >> v;
      update(i, v);
    }
    if (q == 2) {
      std::cin >> i >> j;
      std::cout << get(i, j).i << '\n';
    }
  }
}