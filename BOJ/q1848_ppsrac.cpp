#include <iostream>
#include <vector>
#include <queue>
#include <map>

#define fastio                                                                 \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(nullptr);                                                            \
  cout.tie(nullptr)
#define fori(a, b, c) for (int a = b; a < c; a++)
#define pii pair<int, int>
#define mp(a, b) make_pair(a, b)
#define pb push_back
#define pq priority_queue
using namespace std;
using ll = long long;
const int MAX = 1e9 + 7;

vector<int> dis;
vector<int> adj;
vector<int> in, out;

vector<pii> g[5010];

int n, m;

void dijkstra(int idx, bool t) {
    fori(j, 1, n + 1) { dis[j] = MAX; }
    pq<pii, vector<pii>, greater<pii>> que;
    for (int i = 0; i < adj.size(); i++) {
        if (((i >> idx) & 1) == t) {
            int ii = adj[i];
            que.push({ out[ii], ii });
            dis[ii] = out[ii];
        }
    }
    while (!que.empty()) {
        auto [d, node] = que.top();
        que.pop();
        if (dis[node] < d)
            continue;
        for (auto [dd, son] : g[node]) {
            if (dis[node] + dd < dis[son]) {
                dis[son] = dis[node] + dd;
                que.push({ dis[son], son });
            }
        }
    }
}

int log2(int n) {
    int res = 0;
    while (n) {
        res++;
        n >>= 1;
    }
    return res;
}

int main() {
    fastio;
    cin >> n >> m;

    dis.resize(n + 1);
    in.resize(n + 1);
    out.resize(n + 1);
    while (m--) {
        int u, v, c, d;
        cin >> u >> v >> c >> d;
        if (v != 1 && u != 1) {
            g[u].pb(mp(v, c));
            g[v].pb(mp(u, d));
        }
        else if (v == 1) {
            adj.pb(u);
            out[u] = d;
            in[u] = c;
        }
        else {
            adj.pb(v);
            out[v] = c;
            in[v] = d;
        }
    }
    int N = adj.size();
    int nn = log2(N);
    int ans = MAX;
    fori(i, 0, nn) {
        dijkstra(i, true);
        fori(j, 0, adj.size()) {
            int jj = adj[j];
            if (!(j & (1 << i)))
                ans = min(ans, dis[jj] + in[jj]);
        }
        dijkstra(i, false);
        fori(j, 0, adj.size()) {
            int jj = adj[j];
            if ((j & (1 << i)))
                ans = min(ans, dis[jj] + in[jj]);
        }
    }
    cout << ans;
}