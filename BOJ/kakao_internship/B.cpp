#include <string>
#include <vector>

using namespace std;
const int LEN = 1'000'001;

vector<int> g[LEN];
int incoming[LEN];
bool visited[LEN];

int dfs(int u) {
	visited[u] = true;
	if (g[u].empty()) return 2; // ���� ������ ���� ���� ����: ���� �׷���
	if (g[u].size() == 2) return 3; // ������ ������ �����ϰ� ���� ������ 2: 8�� �׷��� 
	int v = g[u][0];
	if (visited[v]) return 1; // 8�� �׷����� �����ϰ� ����Ŭ�� ����: ���� �׷���
	return dfs(v);
}

// ���� �׷������� ���� ����� ���� 1���� �� �ִٸ� ���� ó�� ���� �� ��ٷο�������,
// ���� ��Ұ� �ݵ�� 2�� �̻��̹Ƿ� ������ ���� ������ �����Ѵ�.
// ������ ���� v�� ����,
// v�� ���� ������ 0�̴�.
// v�� ���� ������ 2 �̻��̴�.
// �׸��� �� ������ �����ϴ� ������ �׻� v �ϳ���.
// ����: ���� ���, 8�� ����� �׻� ����Ŭ�� �̷�Ƿ� ��� ������ ���������� 1 �̻��̴�.
// ���� ����� ��ΰ� �ϳ��̹Ƿ� ���� ������ 0 �Ǵ� 1 �̴�.
vector<int> solution(vector<vector<int>> edges) {
	vector<int> answer(4);

	for (int i = 0; i < edges.size(); ++i) {
		int u = edges[i][0];
		int v = edges[i][1];
		g[u].push_back(v);
		incoming[v]++;
	}
	for (int i = 1; i < LEN; ++i) {
		if (!incoming[i] && g[i].size() >= 2) {
			answer[0] = i;
			break;
		}
	}

	for (const int& u : g[answer[0]]) {
		answer[dfs(u)]++;
	}

	return answer;
}