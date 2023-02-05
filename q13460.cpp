#include <iostream>
#include <queue>

struct Pos { int x, y; };
struct P { Pos red, blue; };
const int INF = 1e9;
char map[11][11];
int visited[11][11][11][11];
int N, M;

void debug(const P& p) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (map[i][j] == 'R') map[i][j] = '.';
			if (map[i][j] == 'B') map[i][j] = '.';
		}
	}
	map[p.red.x][p.red.y] = 'R';
	map[p.blue.x][p.blue.y] = 'B';
	for (int i = 0; i < N; ++i)
		std::cout << map[i] << '\n';
}

P sweep_u(const P& p) {
	int bx = p.blue.x, by = p.blue.y;
	int rx = p.red.x, ry = p.red.y;
	int db, dr;
	for (db = bx; db >= 0; --db) {
		if (map[db - 1][by] == 'O') return { {-1, -1}, {-1, -1} };
		if (map[db - 1][by] == '#') break;
	}
	if (by == ry && rx < bx && rx >= db) ++db;
	for (dr = rx; dr >= 0; --dr) {
		if (map[dr - 1][ry] == 'O') return { {0, 0}, {0, 0} };
		if (map[dr - 1][ry] == '#') break;
	}
	if (ry == by && bx < rx && bx >= dr) ++dr;

	return { {dr, ry}, {db, by} };
}
P sweep_d(const P& p) {
	int bx = p.blue.x, by = p.blue.y;
	int rx = p.red.x, ry = p.red.y;
	int db, dr;
	for (db = bx; db < N; ++db) {
		if (map[db + 1][by] == 'O') return { {-1, -1}, {-1, -1} };
		if (map[db + 1][by] == '#') break;
	}
	if (by == ry && rx > bx && rx <= db) --db;
	for (dr = rx; dr < N; ++dr) {
		if (map[dr + 1][ry] == 'O') return { {0, 0}, {0, 0} };
		if (map[dr + 1][ry] == '#') break;
	}
	if (ry == by && bx > rx && bx <= dr) --dr;

	return { {dr, ry}, {db, by} };
}
P sweep_l(const P& p) {
	int bx = p.blue.x, by = p.blue.y;
	int rx = p.red.x, ry = p.red.y;
	int db, dr;
	for (db = by; db >= 0; --db) {
		if (map[bx][db - 1] == 'O') return { {-1, -1}, {-1, -1} };
		if (map[bx][db - 1] == '#') break;
	}
	if (bx == rx && ry < by && ry >= db) ++db;
	for (dr = ry; dr >= 0; --dr) {
		if (map[rx][dr - 1] == 'O') return { {0, 0}, {0, 0} };
		if (map[rx][dr - 1] == '#') break;
	}
	if (rx == bx && by < ry && by >= dr) ++dr;

	return { {rx, dr}, {bx, db} };
}
P sweep_r(const P& p) {
	int bx = p.blue.x, by = p.blue.y;
	int rx = p.red.x, ry = p.red.y;
	int db, dr;
	for (db = by; db < M; ++db) {
		if (map[bx][db + 1] == 'O') return { {-1, -1}, {-1, -1} };
		if (map[bx][db + 1] == '#') break;
	}
	if (bx == rx && ry > by && ry <= db) --db;
	for (dr = ry; dr < M; ++dr) {
		if (map[rx][dr + 1] == 'O') return { {0, 0}, {0, 0} };
		if (map[rx][dr + 1] == '#') break;
	}
	if (rx == bx && by > ry && by <= dr) --dr;

	return { {rx, dr}, {bx, db} };
}
P(*sweep[4])(const P&) = { sweep_u, sweep_d, sweep_l, sweep_r };

int bfs(const P& p) {
	std::queue<P> q;
	visited[p.red.x][p.red.y][p.blue.x][p.blue.y] = 1;
	q.push(p);

	while (!q.empty()) {
		P cur = q.front(); q.pop();
		if (!cur.red.x) return visited[0][0][0][0] - 1;
		if (visited[cur.red.x][cur.red.y][cur.blue.x][cur.blue.y] == 11) continue;
		for (int i = 0; i < 4; ++i) {
			P next = sweep[i](cur);
			if (!~next.red.x) continue;
			if (visited[next.red.x][next.red.y][next.blue.x][next.blue.y]) continue;
			else {
				visited[next.red.x][next.red.y][next.blue.x][next.blue.y] =
					visited[cur.red.x][cur.red.y][cur.blue.x][cur.blue.y] + 1;
				q.push(next);
			}
		}
	}
	return -1;
}

int main() {
	P init;
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		std::cin >> map[i];
		for (int j = 0; j < M; ++j) {
			if (map[i][j] == 'R') init.red = { i, j }, map[i][j] = '.';
			if (map[i][j] == 'B') init.blue = { i, j }, map[i][j] = '.';
		}
	}
	// for (int i = 0; i < 4; ++i) debug(sweep[i](init));
	std::cout << bfs(init);
}