#include <iostream>
#include <cmath>

typedef long long int ll;

/// <summary>
/// N (<= 1,000,000,000)�� �� �ڸ� ���� d�� �� �� �������� ���ϴ� �Լ�
/// </summary>
/// <param name="d">digit, 0���� 9���� �� �� �ֽ��ϴ�.</param>
/// <param name="n">N, �������� �־��� ��</param>
/// <returns>d�� ������ ������ ��ȯ�մϴ�.</returns>
ll F(int d, ll n) {
	ll result = 0;

	// 1�� �ڸ����� N�� ���ڸ����� ���� �� ���մϴ�.
	for (ll i = 0, k = 1; i <= log10(n); ++i, k *= 10) {
		ll sup = n / k, sub = n % k, digit = sup % 10; sup /= 10;

		// ���� d�� 0�� �ƴ϶�� ���� �����մϴ�.
		if (d)
			result += sup * k + (digit > d ? k : digit == d ? sub + 1 : 0);

		// ���� d�� 0�̰� sup�� 0�� �ƴ϶�� ���� �����մϴ�.
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