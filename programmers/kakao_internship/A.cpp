#include <string>
#include <vector>
#include <map>

using namespace std;
const int LEN = 50;

int N, cnt[LEN][LEN], jisu[LEN], nxt[LEN];
std::map<string, int> idx;

int solution(vector<string> friends, vector<string> gifts) {
	int answer = 0;

	N = friends.size();
	for (int i = 0; i < N; ++i) idx[friends[i]] = i;

	for (int i = 0; i < gifts.size(); ++i) {
		int pivot = gifts[i].find(' ');

		int from = idx[gifts[i].substr(0, pivot)];
		int to = idx[gifts[i].substr(pivot + 1)];

		jisu[from]++; jisu[to]--;
		cnt[from][to]++;
	}

	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			if (cnt[i][j] > cnt[j][i]) nxt[i]++;
			if (cnt[i][j] < cnt[j][i]) nxt[j]++;
			if (cnt[i][j] == cnt[j][i]) {
				if (jisu[i] > jisu[j]) nxt[i]++;
				if (jisu[j] > jisu[i]) nxt[j]++;
			}
		}
	}

	for (int i = 0; i < N; ++i)
		if (nxt[i] > answer)
			answer = nxt[i];

	return answer;
}
