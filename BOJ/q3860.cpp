#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

const int INF = 1e9;
const int LEN = 900;
struct Edge { int u, v, w; };
int W, H, G, E, x1, x2, y1, y2, t;
int map[30][30], dist[LEN];
int flagU[LEN], flagV[LEN];
std::vector<Edge> edges;
std::vector<int> graph[LEN], inv[LEN];

void bfs(int u) {
    std::queue<int> q;
    for (int i = 0; i < W * H; ++i) flagU[i] = i == u;
    q.push(u);
    while (q.size()) {
        u = q.front(); q.pop();
        for (const int& v : graph[u]) {
            if (!flagU[v]) {
                flagU[v] = true;
                q.push(v);
            }
        }
    }
}
void bfs_inv(int v) {
    std::queue<int> q;
    for (int i = 0; i < W * H; ++i) flagV[i] = i == v;
    q.push(v);
    while (q.size()) {
        v = q.front(); q.pop();
        for (const int& u : inv[v]) {
            if (!flagV[u]) {
                flagV[u] = true;
                q.push(u);
            }
        }
    }
}

int bellman_ford(int u, int v) {
    for (int i = 0; i < W * H; ++i) dist[i] = i == u ? 0 : INF;
    for (int i = 0; i < W * H - G; ++i) {
        for (const Edge& e : edges) {
            if (dist[e.u] != INF && dist[e.v] > dist[e.u] + e.w)
                dist[e.v] = dist[e.u] + e.w;
        }
    }
    for (const Edge& e : edges) {
        if (flagU[e.u] && dist[e.v] > dist[e.u] + e.w)
            return -INF; // negetive cycle detected
    }
    return dist[v];
}

bool solve() {
    std::cin >> W >> H;
    if (!W && !H) return false;
    edges.clear();
    for (int i = 0; i < H * W; ++i) graph[i].clear(), inv[i].clear();
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            map[i][j] = 0;
    std::cin >> G;
    for (int g = 0; g < G; ++g) {
        std::cin >> y1 >> x1;
        map[x1][y1] = 1;
    }
    std::cin >> E;
    while (E--) {
        std::cin >> y1 >> x1 >> y2 >> x2 >> t;
        map[x1][y1] = 2;
        Edge e = { x1 * W + y1, x2 * W + y2, t };
        edges.push_back(e);
        graph[x1 * W + y1].push_back(x2 * W + y2);
        inv[x2 * W + y2].push_back(x1 * W + y1);
    }
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (i == H - 1 && j == W - 1) continue;
            if (map[i][j]) continue;
            for (int d = 0, dx = 1, dy = 0; d < 4; ++d) {
                int nx = i + dx, ny = j + dy;
                if (0 <= nx && nx < H && 0 <= ny && ny < W && map[nx][ny] != 1) {
                    Edge e = { i * W + j, nx * W + ny, 1 };
                    edges.push_back(e);
                    graph[i * W + j].push_back(nx * W + ny);
                    inv[nx * W + ny].push_back(i * W + j);
                }
                nx = dx, dx = -dy, dy = nx;
            }
        }
    }
    bfs(0), bfs_inv(W * H - 1);
    int result = bellman_ford(0, W * H - 1);
    if (result == INF) std::cout << "Impossible\n";
    else if (result == -INF) std::cout << "Never\n";
    else std::cout << result << '\n';
    return true;
}

int main() { while (solve()); }