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

int N, K;

int main() {
	std::cin >> N >> K;
	Network nw(N * N * 2 + 5);
	int source = N * N * 2 + 1;
	int sink = N * N * 2 + 2;
	int bottleneck = N * N * 2 + 3;

	nw.add_edge(source, bottleneck, K, 0);
	nw.add_edge(bottleneck, 1, INF, 0);
	nw.add_edge(bottleneck, N * N + 1, INF, 0);
	nw.add_edge(N * N * 2, sink, INF, 0);
	
	for (int i = 0, cap; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> cap;
			nw.add_edge(i * N + j + 1, i * N + j + N * N + 1, 1, -cap);
		}
	}

	for (int i = 0; i < N - 1; ++i) {
		for (int j = 0; j < N; ++j) {
			nw.add_edge(i * N + j + N * N + 1, (i + 1) * N + j + 1, INF, 0);
			nw.add_edge(i * N + j + N * N + 1, (i + 1) * N + j + N * N + 1, INF, 0);
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N - 1; ++j) {
			nw.add_edge(i * N + j + N * N + 1, i * N + j + 2, INF, 0);
			nw.add_edge(i * N + j + N * N + 1, i * N + j + N * N + 2, INF, 0);
		}
	}

	std::cout << -nw.MCMF(source, sink).first << '\n';
}