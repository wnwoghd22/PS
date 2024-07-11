#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <string>
#include <queue>

char cube[6][3][3]; // 0: U, 1: D, 2: F, 3: B, 4: L, 5: R
std::map<std::string, std::string> path;

void init() {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			cube[0][i][j] = 'w'; cube[1][i][j] = 'y';
			cube[2][i][j] = 'r'; cube[3][i][j] = 'o';
			cube[4][i][j] = 'g'; cube[5][i][j] = 'b';
		}
	}
}
void rotate_face(int side, bool ccw) {
	char temp;
	int r = ccw ? 0 : 2, c = ccw ? 2 : 0;
	// rotate corner
	temp = cube[side][0][0];
	cube[side][0][0] = cube[side][r][c];
	cube[side][r][c] = cube[side][2][2];
	cube[side][2][2] = cube[side][c][r];
	cube[side][c][r] = temp;

	// rotate edge
	temp = cube[side][0][1];
	cube[side][0][1] = cube[side][1][c];
	cube[side][1][c] = cube[side][2][1];
	cube[side][2][1] = cube[side][1][r];
	cube[side][1][r] = temp;
}
void rotate_side0(bool ccw) { // U
	char temp[3];
	int l = ccw ? 4 : 5, r = ccw ? 5 : 4;
	for (int i = 0; i < 3; ++i) temp[i] = cube[2][0][i];
	for (int i = 0; i < 3; ++i) cube[2][0][i] = cube[l][0][i];
	for (int i = 0; i < 3; ++i) cube[l][0][i] = cube[3][0][i];
	for (int i = 0; i < 3; ++i) cube[3][0][i] = cube[r][0][i];
	for (int i = 0; i < 3; ++i) cube[r][0][i] = temp[i];
}
void rotate_side1(bool ccw) { // D
	char temp[3];
	int l = ccw ? 4 : 5, r = ccw ? 5 : 4;
	for (int i = 0; i < 3; ++i) temp[i] = cube[2][2][i];
	for (int i = 0; i < 3; ++i) cube[2][2][i] = cube[r][2][i];
	for (int i = 0; i < 3; ++i) cube[r][2][i] = cube[3][2][i];
	for (int i = 0; i < 3; ++i) cube[3][2][i] = cube[l][2][i];
	for (int i = 0; i < 3; ++i) cube[l][2][i] = temp[i];
}
void rotate_side2(bool ccw) { // F
	char temp[3];
	for (int i = 0; i < 3; ++i) temp[i] = cube[0][2][i];

	if (ccw) {
		// 0->4->1->5->0
		for (int i = 0; i < 3; ++i) cube[0][2][i] = cube[5][i][0]; // 5->0
		for (int i = 0; i < 3; ++i) cube[5][2 - i][0] = cube[1][0][i]; // 1->5
		for (int i = 0; i < 3; ++i) cube[1][0][i] = cube[4][i][2]; // 4->1
		for (int i = 0; i < 3; ++i) cube[4][2 - i][2] = temp[i]; // 0->4
	}
	else {
		// 0->5->1->4->0
		for (int i = 0; i < 3; ++i) cube[0][2][i] = cube[4][2 - i][2]; // 4->0
		for (int i = 0; i < 3; ++i) cube[4][i][2] = cube[1][0][i]; // 1->4
		for (int i = 0; i < 3; ++i) cube[1][0][i] = cube[5][2 - i][0]; //5->1
		for (int i = 0; i < 3; ++i) cube[5][i][0] = temp[i]; // 0->5
	}
}
void rotate_side3(bool ccw) { // B
	char temp[3];
	for (int i = 0; i < 3; ++i) temp[i] = cube[0][0][i];

	if (ccw) {
		// 0->5->1->4->0
		for (int i = 0; i < 3; ++i) cube[0][0][i] = cube[4][2 - i][0]; // 4->0
		for (int i = 0; i < 3; ++i) cube[4][i][0] = cube[1][2][i]; // 1->4
		for (int i = 0; i < 3; ++i) cube[1][2][i] = cube[5][2 - i][2]; // 5->1
		for (int i = 0; i < 3; ++i) cube[5][i][2] = temp[i]; // 0->5
	}
	else {
		// 0->4->1->5->0
		for (int i = 0; i < 3; ++i) cube[0][0][i] = cube[5][i][2]; // 5->0
		for (int i = 0; i < 3; ++i) cube[5][2 - i][2] = cube[1][2][i]; // 1->5
		for (int i = 0; i < 3; ++i) cube[1][2][i] = cube[4][i][0]; // 4->1
		for (int i = 0; i < 3; ++i) cube[4][2 - i][0] = temp[i]; // 0->4
	}
}
void rotate_side4(bool ccw) { // L
	char temp[3];
	for (int i = 0; i < 3; ++i) temp[i] = cube[0][i][0];

	if (ccw) {
		// 0->3->1->2->0
		for (int i = 0; i < 3; ++i) cube[0][i][0] = cube[2][i][0]; // 2->0
		for (int i = 0; i < 3; ++i) cube[2][i][0] = cube[1][i][0]; // 1->2
		for (int i = 0; i < 3; ++i) cube[1][i][0] = cube[3][2 - i][2]; // 3->1
		for (int i = 0; i < 3; ++i) cube[3][2 - i][2] = temp[i]; // 0->3
	}
	else {
		// 0->2->1->3->0
		for (int i = 0; i < 3; ++i) cube[0][i][0] = cube[3][2 - i][2]; // 3->0
		for (int i = 0; i < 3; ++i) cube[3][2 - i][2] = cube[1][i][0]; // 1->3
		for (int i = 0; i < 3; ++i) cube[1][i][0] = cube[2][i][0]; // 2->1
		for (int i = 0; i < 3; ++i) cube[2][i][0] = temp[i]; // 0->2
	}
}
void rotate_side5(bool ccw) { // R
	char temp[3];
	for (int i = 0; i < 3; ++i) temp[i] = cube[0][i][2];

	if (ccw) {
		// 0->2->1->3->0
		for (int i = 0; i < 3; ++i) cube[0][i][2] = cube[3][2 - i][0]; // 3->0
		for (int i = 0; i < 3; ++i) cube[3][2 - i][0] = cube[1][i][2]; // 1->3
		for (int i = 0; i < 3; ++i) cube[1][i][2] = cube[2][i][2]; // 2->1
		for (int i = 0; i < 3; ++i) cube[2][i][2] = temp[i]; // 0->2
	}
	else {
		// 0->3->1->2->0
		for (int i = 0; i < 3; ++i) cube[0][i][2] = cube[2][i][2]; // 2->0
		for (int i = 0; i < 3; ++i) cube[2][i][2] = cube[1][i][2]; // 1->2
		for (int i = 0; i < 3; ++i) cube[1][i][2] = cube[3][2 - i][0]; // 3->1
		for (int i = 0; i < 3; ++i) cube[3][2 - i][0] = temp[i]; // 0->3
	}
}

void rotate(char side, bool ccw) {
	switch (side) {
	case 'U':
		rotate_face(0, ccw);
		rotate_side0(ccw);
		break;
	case 'D':
		rotate_face(1, ccw);
		rotate_side1(ccw);
		break;
	case 'F':
		rotate_face(2, ccw);
		rotate_side2(ccw);
		break;
	case 'B':
		rotate_face(3, ccw);
		rotate_side3(ccw);
		break;
	case 'L':
		rotate_face(4, ccw);
		rotate_side4(ccw);
		break;
	case 'R':
		rotate_face(5, ccw);
		rotate_side5(ccw);
		break;
	}
}

std::string get_hash() {
	std::string cur = "";
	for (int k = 0; k < 6; ++k) {
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				cur += cube[k][i][j];
	}
	// std::cout << "hash: " << cur << '\n';
	return cur;
}

void set_cube(const std::string& s) {
	// std::cout << "set hash: " << s << '\n';
	for (int k = 0; k < 6; ++k) {
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				cube[k][i][j] = s[k * 9 + i * 3 + j];
	}
}

void bfs(const std::string& s, const std::string& p) {
	path.clear();
	std::queue<std::string> q;
	q.push(s);
	path[s] = p;
	while (q.size()) {
		std::string now = q.front(); q.pop();
		// std::cout << "now: " << now <<  ", cnt: " << ++cnt << '\n';

		if (path[now].length() == 20) continue;

		std::string nxt;
		set_cube(now);

		rotate('U', 0);
		nxt = get_hash();
		// std::cout << "nxt: " << nxt << '\n';
		if (path.find(nxt) == path.end()) {
			path[nxt] = path[now] + 'U';
			q.push(nxt);
		}

		set_cube(now);
		rotate('U', 1);
		nxt = get_hash();
		// std::cout << "nxt: " << nxt << '\n';
		if (path.find(nxt) == path.end()) {
			path[nxt] = path[now] + 'u';
			q.push(nxt);
		}

		set_cube(now);
		rotate('R', 0);
		nxt = get_hash();
		// std::cout << "nxt: " << nxt << '\n';
		if (path.find(nxt) == path.end()) {
			path[nxt] = path[now] + 'R';
			q.push(nxt);
		}

		set_cube(now);
		rotate('R', 1);
		nxt = get_hash();
		// std::cout << "nxt: " << nxt << '\n';
		if (path.find(nxt) == path.end()) {
			path[nxt] = path[now] + 'r';
			q.push(nxt);
		}
	}
}

bool check(const std::string& s) {
	set_cube(s);
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (cube[1][i][j] != 'y')
				return false;
		}
	}
	for (int i = 1; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (cube[2][i][j] != 'r')
				return false;
		}
	}
	for (int i = 1; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (cube[3][i][j] != 'o')
				return false;
		}
	}
	for (int i = 1; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (cube[4][i][j] != 'g')
				return false;
		}
	}
	for (int i = 1; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (cube[5][i][j] != 'b')
				return false;
		}
	}
	return true;
}

std::map<std::string, std::string> ret;

int main() {
	freopen("cube_17.out", "r", stdin);
	freopen("cube_solution.out", "w", stdout);
	std::string state, p;
	int N;
	std::cin >> N;
	while (std::cin >> state >> p) {
		if (p.length() == 17) {
			bfs(state, p);
			for (auto key : path) {
				if (check(key.first)) {
					if (ret.find(key.first) == ret.end() || key.second.length() < ret[key.first].length())
						ret[key.first] = key.second;
				}
			}
		}
		else if (check(state)) {
			if (ret.find(state) == ret.end() || p.length() < ret[state].length())
				ret[state] = p;
		}
	}
	for (auto key : ret) {
		std::cout << key.first << ' ' << key.second << '\n';
	}
}