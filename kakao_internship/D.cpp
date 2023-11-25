#include <string>
#include <vector>
#include <algorithm>

using namespace std;
const int LEN = 1000;

int N, base, pos[LEN];
int pairs[3][LEN];

int solution(int coin, vector<int> cards) {
	N = cards.size();
	base = N / 3;

	for (int i = 1, j, k; i <= cards.size(); ++i) {
		pos[k = cards[i - 1]] = i;
		if (j = pos[N + 1 - k]) { // pair found
			if (i <= base) pairs[0][i] = 1; // i, j 둘 다 n / 3 중 있음, 비용 0
			else {
				if (j <= base) pairs[1][i] = 1; // 카드 하나는 미리 고름, 비용 1
				else pairs[2][i] = 1; // 둘 다 골라야 할 경우. 비용 2
			}
		}
		for (int d = 0; d < 3; ++d)
			pairs[d][i] += pairs[d][i - 1];
	}

	int answer = 0;
	/*  counter example for naive greedy
	 * 단순한 그리디에 대한 반례는 다음과 같다.
	 * 짝을 맞출 수 있는 숫자들에 대해, 각각의 비용을 나타내는 수열로 바꿨을 때
	 * 다음과 같은 배치가 있다고 하자.
	 *  (0, 0, 0, 0, 0, 2, 0, 2, 0, 1, 0, 1, ...)
	 * 앞서 나온 카드 짝은 비용 2가 소모되고,
	 * 뒤에 나온 카드 짝은 n / 3 중 나머지 짝이 있어 비용이 1이다.
	 * 턴을 계속 이어나가기 위해서는 비용 2인 것을 "반드시 골라야" 하지만,
	 * 비용이 적은 순서대로 고르면 턴을 건너뛰는 경우가 생긴다.
	 * coin이 5인 상황에서 가능한 경우는 앞에서부터 순서대로 골라 3턴까지 버티는 것이지만,
	 * 비용이 적은 순서대로 단순히 고르게 되면 4턴까지 버틸 수 있는 것으로 잘못 계산된다.
	 * 이 반례를 해결하기 위해서는 반드시 골라야 하는 비용 2인 짝을 잘 처리해주면 된다.
	 */
	int necessary_two = 0;
	for (int i = 1; i <= (N - base) / 2; ++i) {
		int cur = base + i * 2;
		int cur_coins = coin;
		int possible_pairs = pairs[0][cur];

		int cost1_pairs = std::min(pairs[1][cur], cur_coins);
		possible_pairs += cost1_pairs;
		cur_coins -= cost1_pairs;

		// 비용 2를 반드시 소모해야 하는 경우를 계산
		while (cur_coins >= 2 && pairs[2][cur] > necessary_two && possible_pairs + necessary_two < i) {
			coin -= 2;
			cur_coins -= 2;
			necessary_two++;
		}

		if (possible_pairs + necessary_two >= i) answer = i;
		else break;
	}
	return answer + 1;
}