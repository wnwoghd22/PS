#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define ll long long
#define LEN 100000
#define MAX 1000000000
#define ABS(x) ((x) >= 0 ? (x) : -(x))

ll sp, temp, stack[LEN];
short cmd[LEN];
char* CMD[12] = {
	"QUIT", "NUM", "POP", "INV", "DUP", "SWP",
	"ADD", "SUB", "MUL", "DIV", "MOD", "END"
};
char buffer[5];
ll X[LEN];
int i, Q, N;
ll div(ll a, ll b) {
	if (!a || !b) return 0;
	ll p = a * b / (ABS(a) * ABS(b));
	return ABS(a) / ABS(b) * p;
}
ll mod(ll a, ll b) {
	if (!a || !b) return 0;
	ll p = a / ABS(a);
	return ABS(a) % ABS(b) * p;
}

int solve() {
	Q = 0;
	while (1) {
		scanf("%s", buffer);
		if (!strcmp(buffer, CMD[0])) return 0;
		if (!strcmp(buffer, CMD[11])) break;
		for (i = 1; i <= 10; ++i) {
			if (!strcmp(buffer, CMD[i])) {
				cmd[Q] = i;
				if (i == 1) scanf("%lld", X + Q);
				break;
			}
		}
		++Q;
	}
	scanf("%d", &N);
	while (N--) {
		scanf("%lld", &stack[0]);
		for (sp = 1, i = 0; i < Q; ++i) {
			switch (cmd[i]) {
			case 1: // NUM
				stack[sp++] = X[i];
				break;
			case 2: // POP
				--sp;
				break;
			case 3: // INV
				if (sp == 0) sp = -1;
				else stack[sp - 1] *= -1;
				break;
			case 4: // DUP
				if (sp == 0) sp = -1;
				else stack[sp] = stack[sp - 1], ++sp;
				break;
			case 5: // SWP
				if (sp < 2) sp = -1;
				else {
					temp = stack[sp - 1];
					stack[sp - 1] = stack[sp - 2];
					stack[sp - 2] = temp;
				}
				break;
			case 6: // ADD
				if (sp < 2) sp = -1;
				else stack[sp - 2] += stack[sp - 1], --sp;
				break;
			case 7: // SUB
				if (sp < 2) sp = -1;
				else stack[sp - 2] -= stack[sp - 1], --sp;
				break;
			case 8: // MUL
				if (sp < 2) sp = -1;
				else stack[sp - 2] *= stack[sp - 1], --sp;
				break;
			case 9: // DIV
				if (sp < 2 || !stack[sp - 1]) sp = -1;
				else stack[sp - 2] = div(stack[sp - 2], stack[sp - 1]), --sp;
				break;
			case 10: // MOD
				if (sp < 2 || !stack[sp - 1]) sp = -1;
				else stack[sp - 2] = mod(stack[sp - 2], stack[sp - 1]), --sp;
				break;
			}
			if (!~sp || sp && ABS(stack[sp - 1]) > MAX) {
				sp = -1;
				break;
			}
		}
		if (sp != 1) printf("ERROR\n");
		else printf("%lld\n", stack[0]);
	}
	printf("\n");
	return 1;
}

int main() { 
	freopen("input.txt", "r", stdin);
	while (solve()); 
}