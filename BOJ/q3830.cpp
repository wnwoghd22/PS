#include <iostream>
#include <cstring>

struct pii { int i, w; };
const int LEN = 100'001;
int weight[LEN];
int p[LEN];

pii find(int i) {
	if (p[i] < 0) return { i, 0 };
	pii q = find(p[i]);
	p[i] = q.i;
	weight[i] += q.w;
	return { p[i], weight[i] };
}

int join(int a, int b, int w) {
	pii _a = find(a), _b = find(b);
	if (_a.i == _b.i) return false;
	if (p[_a.i] < p[_b.i]) {
		weight[_b.i] = _a.w + w - _b.w;
		p[_a.i] += p[_b.i];
		p[_b.i] = _a.i;
	}
	else {
		weight[_a.i] = _b.w - w - _a.w;
		p[_b.i] += p[_a.i];
		p[_a.i] = _b.i;
	}
	return true;
}

bool solve() {
	memset(p, -1, sizeof p);
	memset(weight, 0, sizeof weight);
	int N, M, a, b, w;
	char q;
	std::cin >> N >> M;
	if (!N && !M) return false;
	while (M--) {
		std::cin >> q;
		if (q == '!') {
			std::cin >> a >> b >> w;
			join(a, b, w);
		}
		if (q == '?') {
			std::cin >> a >> b;
			pii _a = find(a), _b = find(b);
			if (_a.i == _b.i) std::cout << _b.w - _a.w << '\n';
			else std::cout << "UNKNOWN\n";
		}
	}
	return true;
}

int main() { while (solve()); }