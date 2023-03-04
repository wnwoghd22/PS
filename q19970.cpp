#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

struct Vector { 
	int x, y, z;
	Vector operator-(const Vector& r) const { return { x - r.x, y - r.y, z - r.z }; }
	Vector operator*(const Vector& r) const { 
		return {
			y * r.z - z * r.y,
			z * r.x - x * r.z,
			x * r.y - y * r.x
		};
	}
	
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
	if (line1[0] == line2[0] || line1[1] == line2[0] || line1[1] == line2[0] || line1[1] == line2[1]) {
		std::cout << "Yes";
	}
	else {
		// get plane
		Vector p1 = pos[line1[0]];
		Vector p2 = pos[line1[1]];
		Vector p3 = pos[line2[0]];
		Vector p4 = pos[line2[1]];

		Vector v1 = p2 - p1;
		Vector v2 = p3 - p1;
		Vector norm = v1 * v2;
		int d = p1.x * norm.x + p1.y * norm.y + p1.z * norm.z;
		std::cout << norm.x << ' ' << norm.y << ' ' << norm.z << ' ' << d << '\n';
		int result = norm.x * p4.x + norm.y * p4.y + norm.z * p4.z + d;
		if (result) {
			// std::cout << "not on a plane.\n";
			std::cout << "No";
		}
		else {
			std::cout << "On the same plane.";
		}
	}
}