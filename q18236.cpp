#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>

#define MAX 200'001

namespace HuShing {
	typedef long long int ll;
	typedef std::pair<int, int> pii;
	class HArc;
	int w[MAX + 1];
	int n;
	ll cp[MAX];
	int hnum;
	HArc* h[MAX];
	std::vector<HArc*> adjacent[MAX]; // push h-arc if an arc is processed temporarily

	class HArc {
	public:
		int idx, u, v, min;
		ll mul, num, den, base; // numerator, denominator
		std::vector<HArc*> children;

		HArc(int u, int v) :
			idx(++hnum), u(u), v(v), min(w[u] < w[v] ? u : v),
			mul((ll)w[u] * w[v]), num(0), den(cp[v] - cp[u] - mul), base(cp[v] - cp[u] - mul) {
			h[idx] = this;
		}
		ll getSupportWeight() { return num / den; } // C(Hn,Hk) / (Wk:Wk') - Wk*Wk'
		struct compare {
			bool operator()(HArc* l, HArc* r) {
				return l->getSupportWeight() < r->getSupportWeight();
			}
		};
		std::priority_queue<HArc*, std::vector<HArc*>, compare> ceil;

		bool isAbove(HArc* other) { return u <= other->u && other->v <= v; }

		ll get_min_mul() {
			if (idx == 1) return (ll)w[1] * w[2] + (ll)w[1] * w[n];

			if (u == min) {
				if (!adjacent[u].empty() && isAbove(adjacent[u].back()))
					return adjacent[u].back()->mul;
				else return (ll)w[u] * w[u + 1];
			}
			else {
				if (!adjacent[v].empty() && isAbove(adjacent[v].back()))
					return adjacent[v].back()->mul;
				else return (ll)w[v] * w[v - 1];
			}
		}
		ll H0() { // cost of fan
			// upper sum is Wu*W(u+1) + W(u+1)*W(u+2) + ... + W(v-1)*Wv
			// subtract WuW(u+1) and multiply Wu to get Wu*(W(u+1):Wv) = Fan(Wu|W(u+1):Wv)
			return (ll)w[min] * (den + mul - get_min_mul());
		}

		void remove(HArc* h) {
			den += h->den;
			adjacent[h->u].pop_back();
			adjacent[h->v].pop_back();
			num = H0(); // renew the cost of Fan
		}
		void condense(HArc* h) {
			// condense cost
			den += h->den;
			num += h->num;

			adjacent[h->u].pop_back();
			adjacent[h->v].pop_back();
		}

		void dfs() {
			if (children.empty()) { // leaf node
				num = H0(); // numrator is the cost of Fan

				// make self ceil to check either positive or negative
				adjacent[u].push_back(this);
				adjacent[v].push_back(this);
				ceil.push(this);
				return;
			}

			for (HArc* c : children) {
				c->dfs();
				// remove (Wi:Wi') and add (Wi*Wi')
				den -= c->base;
				while (!c->ceil.empty())
					ceil.push(c->ceil.top()), c->ceil.pop(); // merge priority queue
			}
			// get local optimum cost of subpolygon(Fan) bounced above by sons
			num = H0();

			while (!ceil.empty() && ceil.top()->getSupportWeight() >= w[min]) { // delete
				remove(ceil.top()), ceil.pop();
			}
			while (!ceil.empty() && getSupportWeight() <= ceil.top()->getSupportWeight()) { // condense
				condense(ceil.top()), ceil.pop();
			}

			adjacent[u].push_back(this);
			adjacent[v].push_back(this);
			ceil.push(this);
		}
	};

	void get_cp() {
		int* V1 = std::min_element(w + 1, w + n + 1);
		std::rotate(w + 1, V1, w + n + 1);
		w[n + 1] = w[1];

		memset(cp, 0, sizeof cp);
		for (int i = 1; i <= n + 1; ++i) {
			cp[i] = (ll)w[i] * w[i - 1];
			cp[i] += cp[i - 1];
		}
	}
	HArc* build_tree(std::vector<pii>& potential) {
		hnum = 0;
		std::vector<HArc*> _stack;
		HArc* root = new HArc(1, n + 1);

		for (const pii& p : potential) {
			HArc* h = new HArc(p.first, p.second);
			while (!_stack.empty() && h->isAbove(_stack.back())) {
				h->children.push_back(_stack.back());
				_stack.pop_back();
			}
			_stack.push_back(h);
		}
		while (!_stack.empty()) {
			root->children.push_back(_stack.back());
			_stack.pop_back();
		}
		return root;
	}
	HArc* one_sweep() {
		std::vector<int> _stack;
		std::vector<pii> temp, h_list;

		for (int i = 1; i <= n; ++i) {
			while (_stack.size() > 1 && w[_stack.back()] > w[i]) { // if Wt > Wc
				temp.push_back({ _stack[_stack.size() - 2], i }); // push V(t-1)-Vc arc
				_stack.pop_back(); // pop Vt
			}
			_stack.push_back(i); // push Vc
		}
		while (_stack.size() > 3) {
			temp.push_back({ 1, _stack[_stack.size() - 2] }); // push V(t-1)
			_stack.pop_back();
		}
		for (const pii& p : temp) {
			if (p.first == 1 || p.second == 1) continue;
			h_list.push_back(p);
		}
		return build_tree(h_list);
	}

	ll HMCM() {
		int a, i;
		ll result = 0;
		std::cin >> n;

		++n;

		memset(w, 0, sizeof w);
		std::cin >> w[1] >> w[2];
		for (i = 3; i <= n; ++i) std::cin >> a >> w[i];

		if (n < 3) {
			std::cout << 0;
			return 0;
		}

		get_cp();
		HArc* root = one_sweep();
		root->dfs();

		while (!root->ceil.empty()) {
			result += root->ceil.top()->num;
			root->ceil.pop();
		}

		std::cout << result;

		return result;
	}
}

int main() {
	HuShing::HMCM();
}
