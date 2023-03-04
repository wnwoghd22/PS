#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

struct Pos { 
	int x, y, z;
} pos[8] = {
	{ 0, 0, 0 },
	{ 0, 0, 1 },
	{ 1, 0, 1 },
	{ 1, 0, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 1 },
	{ 1, 1, 1 },
	{ 1, 1, 0 }
};

char s[5];
int line1[2], line2[2];

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> s;
	for (int i = 0, j = -1; s[i]; ++i) {
		if (s[i] == '1') line1[j] += 4;
		else line1[++j] = s[i] - 'A';
	}
	std::cin >> s;
	for (int i = 0, j = -1; s[i]; ++i) {
		if (s[i] == '1') line2[j] += 4;
		else line2[++j] = s[i] - 'A';
	}
	for (int i = 0; i < 2; ++i) {
		const Pos& p = pos[line1[i]];
		std::cout << p.x << ' ' << p.y << ' ' << p.z << '\n';
	}
	for (int i = 0; i < 2; ++i) {
		const Pos& p = pos[line2[i]];
		std::cout << p.x << ' ' << p.y << ' ' << p.z << '\n';
	}
}