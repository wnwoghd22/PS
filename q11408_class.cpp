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

int N, M;

int main() {
	std::cin >> N >> M;
	Network network(N + M + 3);

	for (int i = 1; i <= N; ++i) network.add_edge(N + M + 1, i, 1, 0);
	for (int i = 1; i <= M; ++i) network.add_edge(N + i, N + M + 2, 1, 0); 
	for (int K, v, dst, u = 1; u <= N; ++u) {
		std::cin >> K;
		while (K--) {
			std::cin >> v >> dst;
			network.add_edge(u, N + v, 1, dst);
		}
	}
	auto result = network.MCMF(N + M + 1, N + M + 2);

	std::cout << result.second << '\n' << result.first;
}