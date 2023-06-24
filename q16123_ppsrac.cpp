#include <iostream>
#include <unordered_map>
using namespace std;

#define fastio ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr)
#define ll long long
#define fori(a, b, c) for(ll a = b; a < c; a++)

vector<ll> S_mu;

void init() {
	S_mu.resize(2000011);
	S_mu[0] = 0; S_mu[1] = 1;
	fori(i, 1, 2000000) {
		for (ll j = 2; j * i < 2000000; j++) S_mu[j * i] -= S_mu[i];
		S_mu[i] += S_mu[i - 1];
	}
}

unordered_map<ll, ll> mp;

ll S(ll x) {
	ll i, j;
	if (x <= 2000000) return S_mu[x];
	if (mp.find(x) != mp.end()) return mp[x];
	ll res = 1;
	for (i = 2; i <= x; i = j + 1) {
		j = x / (x / i);
		res -= (j - i + 1) * S(x / i);
	}
	return mp[x] = res;
}

ll S_odd(ll x) {
	ll res = 0;
	while (x) {
		res += S(x); x >>= 1;
	}
	return res;
}

ll S_even(ll x) {
	return S(x) - S_odd(x);
}

ll solve(ll n) {
	ll i, j;
	ll res = 0;
	for (i = 1; i <= n; i = j + 2) {
		j = n / (n / i);
		if (!(j & 1)) j--;
		res += ((n / i) * ((n / i) >> 1)) * (S_odd(j) - S_odd(i - 1));
	}
	for (i = 2; i <= n; i = j + 2) {
		j = n / (n / i);
		if (j & 1)j--;
		res += ((n / i) * (n / i)) * (S_even(j) - S_even(i - 1));
	}
	return res;
}

int main() {
	ll L; cin >> L;
	init();
	cout << solve(L);
}