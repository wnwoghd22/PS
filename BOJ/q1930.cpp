#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>

short topo[4][3] = {
	1, 2, 3, // 0
	3, 2, 0, // 1
	0, 1, 3, // 2
	2, 1, 0  // 3
};

int K, a0[4], a1[4];

int f() {
	for (int i = 0; i < 4; ++i) {
		if (a0[i] != a1[0]) continue;
		// printf("under: %d\n", i);
		for (int j = 0; j < 3; ++j) {
			bool flag = 1;
			// printf("check %d\n", j);
			for (int k = 0; k < 3; ++k) {
				// printf("side: (%d, %d): %d, %d\n", (k + j) % 3, k, a0[topo[i][(k + j) % 3]], a1[topo[0][k]]);
				if (a0[topo[i][(k + j) % 3]] != a1[topo[0][k]]) {
					flag = 0;
					break;
				}
			}
			if (flag) return 1;
		}
	}
	return 0;
}

int main() {
	scanf("%d", &K);
	while (K--) {
		scanf("%d%d%d%d", a0, a0 + 1, a0 + 2, a0 + 3);
		scanf("%d%d%d%d", a1, a1 + 1, a1 + 2, a1 + 3);
		printf("%d\n", f());
	}
}