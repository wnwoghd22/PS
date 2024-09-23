#include <string>
#include <vector>

using namespace std;
const int LEN = 1'000'001;

vector<int> g[LEN];
int incoming[LEN];
bool visited[LEN];

int dfs(int u) {
	visited[u] = true;
	if (g[u].empty()) return 2;
	if (g[u].size() == 2) return 3;
	int v = g[u][0];
	if (visited[v]) return 1;
	return dfs(v);
}

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