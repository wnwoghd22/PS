#include <iostream>

const int LEN = 50'001;
int phi[LEN];

void init() {
	for (int i = 0; i < LEN; ++i) phi[i] = i;
	for (int i = 2; i < LEN; ++i) {
		if (phi[i] == i) {
			for (int j = i; j < LEN; j += i)
				phi[j] /= i, phi[j] *= i - 1;
		}
	}
}