#include <iostream>

char S[3];
int kx, ky;
int sx, sy;
int N, dx, dy, nx, ny, snx, sny;

int main() {
	std::cin >> S;
	kx = S[0] - 'A';
	ky = S[1] - '1';
	
	std::cin >> S;
	sx = S[0] - 'A';
	sy = S[1] - '1';

	std::cin >> N;
	while (N--) {
		std::cin >> S;
		dx = dy = 0;
		for (int i = 0; S[i]; ++i) {
			if (S[i] == 'B') dy--;
			if (S[i] == 'T') dy++;
			if (S[i] == 'R') dx++;
			if (S[i] == 'L') dx--;
		}
		nx = kx + dx;
		ny = ky + dy;
		if (0 <= nx && nx <= 7 && 0 <= ny && ny <= 7) {
			if (nx == sx && ny == sy) {
				snx = sx + dx;
				sny = sy + dy;
				if (0 <= snx && snx <= 7 && 0 <= sny && sny <= 7) {
					sx = snx;
					sy = sny;
				}
				else continue;
			}
			kx = nx;
			ky = ny;
		}
	}
	S[0] = kx + 'A', S[1] = ky + '1'; std::cout << S << '\n';
	S[0] = sx + 'A', S[1] = sy + '1'; std::cout << S << '\n';
}