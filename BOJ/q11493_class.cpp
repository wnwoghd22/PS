#include <iostream>
#include <vector>
#include <queue>

const int INF = 1e9;

class Network {
private:
	struct Edge {
	public:
		int to, capacity, flow, cost;
		Edge* rev;
		Edge() : to(0), capacity(0), flow(0), cost(0), rev(0) {}
		Edge(int to, int capacity, int cost) : to(to), capacity(capacity), flow(0), cost(cost), rev(0) {}
		int remain() const { return capacity - flow; }
		void add_flow(int flow) {
			this->flow += flow;
			rev->flow -= flow;
		}
	};
	std::vector<std::vector<Edge*>> adj;
public:
	Network(int size) { adj.resize(size); }
	~Network() { for (std::vector<Edge*>& v : adj) for (Edge* e : v) delete e; }
	void add_edge(int u, int v, int capacity, int cost) {
		Edge* uv = new Edge(v, capacity, cost);
		Edge* vu = new Edge(u, 0, -cost);
		uv->rev = vu; vu->rev = uv;
		adj[u].push_back(uv);
		adj[v].push_back(vu);
	}
	std::pair<int, int> MCMF(int source, int sink) {
		int mc = 0, mf = 0;
		int _size = adj.size();

		while (true) {
			std::queue<int> q;
			std::vector<bool> inQ(_size, false);
			std::vector<int> dist(_size, INF);
			std::vector<int> parent(_size, 0);
			std::vector<Edge*> path(_size, 0);

			dist[source] = 0;
			q.push(source);
			inQ[source] = true;

			while (!q.empty()) {
				int u = q.front(); q.pop(); inQ[u] = false;

				for (Edge* e : adj[u]) { // u -> v
					int v = e->to;
					if (e->remain() > 0 && dist[u] + e->cost < dist[v]) {
						dist[v] = dist[u] + e->cost;
						parent[v] = u;
						path[v] = e;
						if (!inQ[v]) {
							q.push(v);
							inQ[v] = true;
						}
					}
				}
			}
			if (!parent[sink]) break;

			int flow = INF;

			for (int i = sink; i ^ source; i = parent[i]) flow = std::min(flow, path[i]->remain());
			for (int i = sink; i ^ source; i = parent[i]) {
				path[i]->add_flow(flow);
				mc += flow * path[i]->cost;
			}
			mf += flow;
		}
		return { mc, mf };
	}
};

int T, N, M, x, y;

void solve() {
	std::cin >> N >> M;
	Network network(N + 3);
	std::vector<int> coin(N + 3), pos(N + 3);
	while (M--) {
		std::cin >> x >> y;
		network.add_edge(x, y, INF, 1);
		network.add_edge(y, x, INF, 1);
	}
	for (int i = 1; i <= N; ++i) std::cin >> pos[i];
	for (int i = 1; i <= N; ++i) std::cin >> coin[i];
	for (int i = 1; i <= N; ++i) {
		if (coin[i] && !pos[i]) network.add_edge(N + 1, i, 1, 0);
		if (!coin[i] && pos[i]) network.add_edge(i, N + 2, 1, 0);
	}
	std::cout << network.MCMF(N + 1, N + 2).first << '\n';
}

int main() {
	std::cin >> T;
	while (T--) solve();
}