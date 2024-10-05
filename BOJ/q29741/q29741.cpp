#include <vector>
#include "coreputer.h"

std::vector<int> malfunctioning_cores(int N) {
	std::vector<int> ret(N, 0);
	std::vector<int> p(N);
	std::vector<int> q;
	int l = 0, r = N - 1, m;
	while (l < r) {
		m = l + r >> 1;
		q.clear();
		for (int i = 0; i <= m; ++i) q.push_back(i);
		if ((p[m] = run_diagnostic(q)) >= 0) r = m;
		else l = m + 1;
	}
	ret[l] = 1;
	if (l == N - 1) return ret;

	int cl = 1 - p[l], cr = 0;
	for (int i = 0; i < l; ++i) {
		q.clear();
		for (int j = 0; j <= l; ++j) {
			if (j != i) 
				q.push_back(j);
		}
		if (run_diagnostic(q) < 0) cl += ret[i] = 1;
	}
	for (int i = l + 1; i < N - 1; ++i) {
		q.clear();
		for (int j = l; j < N; ++j) {
			if (j != i)
				q.push_back(j);
		}
		if (run_diagnostic(q) <= 0) cr += ret[i] = 1;
	}
	ret[N - 1] = cl > cr;

	return ret;
}