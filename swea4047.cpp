#include <stdio.h>

char s[1001];
int get_deck(char c) {
	switch (c) {
	case 'S': return 0;
	case 'D': return 1;
	case 'H': return 2;
	case 'C': return 3;
	}
}
int deck[4][13], cnt[4];

void solve(int t) {
	printf("#%d ", t);
	int i, j, d, k;
	scanf("%s", s);
	for (i = 0; i < 4; ++i) {
		cnt[i] = 13;
		for (j = 0; j < 13; ++j) deck[i][j] = 0;
	}
	for (i = 0; s[i]; i += 3) {
		d = get_deck(s[i]), k = (s[i + 1] - '0') * 10 + s[i + 2] - '0' - 1;
		if (deck[d][k]++) {
			printf("ERROR\n");
			return;
		}
		--cnt[d];
	}
	printf("%d %d %d %d\n", cnt[0], cnt[1], cnt[2], cnt[3]);
}

int main() {
	int t, T;
	scanf("%d", &T);
	for (t = 1; t <= T; ++t) solve(t);
}