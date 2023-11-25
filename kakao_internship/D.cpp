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
			if (i <= base) pairs[0][i] = 1; // i, j �� �� n / 3 �� ����, ��� 0
			else {
				if (j <= base) pairs[1][i] = 1; // ī�� �ϳ��� �̸� ��, ��� 1
				else pairs[2][i] = 1; // �� �� ���� �� ���. ��� 2
			}
		}
		for (int d = 0; d < 3; ++d)
			pairs[d][i] += pairs[d][i - 1];
	}

	int answer = 0;
	/*  counter example for naive greedy
	 * �ܼ��� �׸��� ���� �ݷʴ� ������ ����.
	 * ¦�� ���� �� �ִ� ���ڵ鿡 ����, ������ ����� ��Ÿ���� ������ �ٲ��� ��
	 * ������ ���� ��ġ�� �ִٰ� ����.
	 *  (0, 0, 0, 0, 0, 2, 0, 2, 0, 1, 0, 1, ...)
	 * �ռ� ���� ī�� ¦�� ��� 2�� �Ҹ�ǰ�,
	 * �ڿ� ���� ī�� ¦�� n / 3 �� ������ ¦�� �־� ����� 1�̴�.
	 * ���� ��� �̾���� ���ؼ��� ��� 2�� ���� "�ݵ�� ����" ������,
	 * ����� ���� ������� ���� ���� �ǳʶٴ� ��찡 �����.
	 * coin�� 5�� ��Ȳ���� ������ ���� �տ������� ������� ��� 3�ϱ��� ��Ƽ�� ��������,
	 * ����� ���� ������� �ܼ��� ���� �Ǹ� 4�ϱ��� ��ƿ �� �ִ� ������ �߸� ���ȴ�.
	 * �� �ݷʸ� �ذ��ϱ� ���ؼ��� �ݵ�� ���� �ϴ� ��� 2�� ¦�� �� ó�����ָ� �ȴ�.
	 */
	int necessary_two = 0;
	for (int i = 1; i <= (N - base) / 2; ++i) {
		int cur = base + i * 2;
		int cur_coins = coin;
		int possible_pairs = pairs[0][cur];

		int cost1_pairs = std::min(pairs[1][cur], cur_coins);
		possible_pairs += cost1_pairs;
		cur_coins -= cost1_pairs;

		// ��� 2�� �ݵ�� �Ҹ��ؾ� �ϴ� ��츦 ���
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