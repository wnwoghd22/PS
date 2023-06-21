#include <iostream>

const int LEN = 50'001;
int mu[LEN] = { 0, 1, };

void init() {
	for (int i = 1; i < LEN; ++i) {
		if (mu[i]) {
			for (int j = i << 1; j < LEN; j += i)
				mu[j] -= mu[i];
		}
	}
}