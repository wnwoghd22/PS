#include <iostream>
#include <algorithm>

const int LEN = 100;

int N, A[LEN], B;


struct Box { int b, l; } stack[LEN];
int sp;

struct Segment { int l, r, h; } seg[LEN];
int sp2, stack2[LEN];


int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> A[i];
		B = A[i];
		while (sp) {
			if (A[i] <= stack[sp - 1].l) {
				B = std::max(B, stack[sp - 1].b + 2 * A[i]);
				break;
			}
			else {
				B = std::max(B, stack[sp - 1].b + 2 * stack[sp - 1].l);
				--sp;
			}
		}
		seg[i] = { B - A[i], B + A[i], A[i] };
		stack[sp++] = { B, A[i] };
	}
	for (int i = 0, j, f; i < N; ++i) {
		// std::cout << seg[i].l << ' ' << seg[i].r << '\n';
		f = 1;
		while (sp2) {
			j = stack2[sp2 - 1];
			if (seg[i].h <= seg[j].h) {
				if (seg[i].r <= seg[j].r) { f = 0; break; }
				seg[i].l = seg[j].r;
				break;
			}
			else {
				if (seg[i].l > seg[j].l) break;
				--sp2;
			}
		}
		if (f) stack2[sp2++] = i;
	}
	for (int i = 0; i < sp2; ++i) std::cout << stack2[i] + 1 << ' ';
}