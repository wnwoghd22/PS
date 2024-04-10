#include <iostream>

double A, B, X, Sa, Sb; 

int main() { 
	std::cout << std::fixed;
	std::cout.precision(10);
	std::cin >> A >> B >> X;
	if (A > B) Sa = X / A, Sb = (100 - X) / B;
	else Sb = X / B, Sa = (100 - X) / A;
	std::cout << Sa << ' ' << Sb << '\n';
	std::cout << 100 / (Sa + Sb); 
}