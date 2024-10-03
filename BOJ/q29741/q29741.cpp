#include <vector>
#include <iostream>

#include "coreputer.h"

std::vector<int> malfunctioning_cores(int N) {
	std::vector<int> ret(N, 0);
	std::vector<int> q;
	int l = 0, r = N - 1, m;
	while (l < r) {
		m = l + r >> 1;
		std::cout << "l: " << l << " r: " << r << " m: " << m << '\n';
		q.clear();
		for (int i = 0; i <= m; ++i) q.push_back(i);
		if (run_diagnostic(q) >= 0) r = m;
		else l = m + 1;
	}
	ret[l] = 1;
	
	std::cout << "mid: " << l << '\n';

	int cl = 0, cr = 0;
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

	return ret;
}