#include <iostream>
#include <cmath>

typedef long long int ll;

/// <summary>
/// N (<= 1,000,000,000)에 한 자리 숫자 d가 몇 번 나오는지 구하는 함수
/// </summary>
/// <param name="d">digit, 0부터 9까지 들어갈 수 있습니다.</param>
/// <param name="n">N, 문제에서 주어진 수</param>
/// <returns>d가 나오는 개수를 반환합니다.</returns>
ll F(int d, ll n) {
	ll result = 0;

	// 1의 자리부터 N의 끝자리까지 값을 다 더합니다.
	for (ll i = 0, k = 1; i <= log10(n); ++i, k *= 10) {
		ll sup = n / k, sub = n % k, digit = sup % 10; sup /= 10;

		// 만약 d가 0이 아니라면 값을 누적합니다.
		if (d)
			result += sup * k + (digit > d ? k : digit == d ? sub + 1 : 0);

		// 만약 d가 0이고 sup이 0이 아니라면 값을 누적합니다.
		else if (sup)
			result += (sup - 1) * k + (digit ? k : sub + 1);
	}
	return result;
}

int main() {
	int N;
	std::cin >> N;
	for (int i = 0; i < 10; ++i) {
		std::cout << F(i, N) << ' ';
	}
}