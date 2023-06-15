#include <iostream>

typedef long long ll;
const ll P = 99991;
const ll A = 55048, B = 44944, C = 22019;

const int PP = 33330; // pisano period
ll a[PP] = { 1, }, b[PP] = { 1, };

ll pow(ll a, ll b, ll m) {
	ll r = 1;
	while (b) {
		if (b & 1)
			r = r * a % m;
		a = a * a % m;
		b >>= 1;
	}
	return r;
}
ll fibo(ll n) { return (pow(A, n, P) - pow(B, n, P) + P) * C % P; }

int main() {
	for (int i = 1; i < PP; ++i) {
		a[i] = a[i - 1] * A % P;
		b[i] = b[i - 1] * B % P;
	}

}