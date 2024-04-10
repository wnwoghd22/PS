#include <iostream>
#include <map>

typedef long long int ll;
std::map<int, ll> Sa, Sb;
int Aa[1000], Ab[1000];
int N, M, T;

int main() {
	ll result = 0;
	std::cin >> T;

	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> Aa[i];
	for (int i = 0; i < N; ++i) {
		for (int j = i, s = 0; j < N; ++j) {
			s += Aa[j];
			if (Sa.find(s) == Sa.end()) Sa[s] = 1;
			else Sa[s]++;
		}
	}
	std::cin >> M;
	for (int i = 0; i < M; ++i) std::cin >> Ab[i];
	for (int i = 0; i < M; ++i) {
		for (int j = i, s = 0; j < M; ++j) {
			s += Ab[j];
			if (Sb.find(s) == Sb.end()) Sb[s] = 1;
			else Sb[s]++;
		}
	}
	for (const auto& [k, v] : Sa) {
		if (Sb.find(T - k) != Sb.end())
			result += v * Sb[T - k];
	}
	std::cout << result;
}