#include <string>
#include <vector>

using namespace std;
const int LEN = 1'000'001;

vector<int> g[LEN];
int incoming[LEN];
bool visited[LEN];

int dfs(int u) {
	visited[u] = true;
	if (g[u].empty()) return 2; // 진출 간선이 없는 정점 존재: 막대 그래프
	if (g[u].size() == 2) return 3; // 생성된 정점을 제외하고 진출 차수가 2: 8자 그래프 
	int v = g[u][0];
	if (visited[v]) return 1; // 8자 그래프를 제외하고 사이클이 존재: 도넛 그래프
	return dfs(v);
}

// 원본 그래프에서 연결 요소의 수가 1개일 수 있다면 예외 처리 등이 꽤 까다로웠겠지만,
// 연결 요소가 반드시 2개 이상이므로 다음과 같은 성질이 성립한다.
// 생성된 정점 v에 대해,
// v의 진입 차수는 0이다.
// v의 진출 차수는 2 이상이다.
// 그리고 이 조건을 만족하는 정점은 항상 v 하나다.
// 증명: 도넛 모양, 8자 모양은 항상 사이클을 이루므로 모든 정점의 진입차수는 1 이상이다.
// 막대 모양은 경로가 하나이므로 진출 차수는 0 또는 1 이다.
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