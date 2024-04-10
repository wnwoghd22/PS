#include <iostream>
#include <cmath>

typedef long long int ll;

double f(ll A, ll B, ll x) { return B * x + A / sqrt(x + 1); }
double f_1(double A, double B) { return pow(A / (2 * B), 2.0 / 3) - 1; }

int main() {
	ll A, B;
	std::cin >> A >> B;
	double minima = f_1(A, B);
	double r = f(A, B, ceil(minima));
	double l = f(A, B, floor(minima));

	std::cout << std::fixed;
	std::cout.precision(10);
	std::cout << std::min(l, r);
}