#include <iostream>
#include <queue>
#include <set>

const int WID = 1001;
const int LEN = 1e6 + 1;
const int INF = 1e9 + 1;
const int SOURCE = 0;
const int SINK = LEN - 1;

char map[WID][WID];
int mask[WID][WID];
bool visited[WID][WID];

int weight[LEN];
struct Info { 
	int u, w;
	bool operator<(const Info& r) const { return w > r.w; }
};
std::set<int> graph[LEN];
std::priority_queue<Info> pq;

int dist[LEN];
int N;

void rotate90(int& x, int& y) { int t = x; x = -y; y = t; }
void rotate45(int& x, int& y) {
	int nx = x - y, ny = x + y;
	x = nx ? nx / abs(nx) : 0; 
	y = ny ? ny / abs(ny) : 0;
}

void bfs_mask(int i, int j) {
	std::queue<int> q;
	int m = i * N + j;
	mask[i][j] = m;
	q.push(m);

	while (q.size()) {
		int x = q.front() / N, y = q.front() % N;
		q.pop();
		++weight[m];

		for (int d = 0, dx = 0, dy = 1, t; d < 4; ++d, rotate90(dx, dy)) {
			int nx = x + dx, ny = y + dy;
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
			if (map[x][y] ^ map[nx][ny]) continue;
			if (mask[nx][ny]) continue;

			mask[nx][ny] = m;
			q.push(nx * N + ny);
		}
	}
}

void bfs_edge(int i, int j) {
	std::queue<int> q;
	int m = i * N + j;
	visited[i][j] = 1;
	q.push(m);

	while (q.size()) {
		int x = q.front() / N, y = q.front() % N;
		q.pop();

		for (int d = 0, dx = 0, dy = 1, t; d < 8; ++d, rotate45(dx, dy)) {
			int nx = x + dx, ny = y + dy;
			if (nx < 0 || ny >= N) {
				graph[m].insert(SINK);
				continue;
			}
			if (ny < 0 || nx >= N) {
				graph[SOURCE].insert(m);
				continue;
			}
			if (mask[x][y] ^ mask[nx][ny]) {
				graph[m].insert(mask[nx][ny]);
				continue;
			}
			if (visited[nx][ny]) continue;

			visited[nx][ny] = 1;
			q.push(nx * N + ny);
		}
	}
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> map[i];
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (!mask[i][j])
				bfs_mask(i, j);
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j)
			std::cout << mask[i][j] << ' ';
		std::cout << '\n';
	}
	for (int i = 0; i < N * N; ++i) {
		std::cout << weight[i] << ' ';
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (i * N + j == 0 || i * N + j == N * N - 1) continue;
			if (!visited[i][j])
				bfs_edge(i, j);
		}
	}
	for (int i = 0; i < N * N; ++i) dist[i] = INF;
	dist[SINK] = INF;

	dist[SOURCE] = 0;
	pq.push({ SOURCE, 0 });
	while (pq.size()) {
		Info i = pq.top(); pq.pop();
		std::cout << "cur: " << i.u << ' ' << i.w << '\n';
		if (i.w > dist[i.u]) continue;
		for (const int& v : graph[i.u]) {
			std::cout << i.u << " -> " << v << '\n';
			if (i.w + weight[v] < dist[v]) {
				pq.push({ v, dist[v] = i.w + weight[v] });
			}
		}
	}
	std::cout << dist[SINK];
}