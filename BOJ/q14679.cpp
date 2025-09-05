#include <iostream>

typedef long long ll;
const ll MOD = 1e9 + 7;

int p(int a, int b) {
	int ret = 1;
	while (b) {
		if (b & 1) ret = ret * a % 1000;
		a = a * a % 1000; b >>= 1;
	}
	return ret;
}

int N;
ll A, D, H, MA, MD, MH, Ap, Aa, Dp, Da, Hp, Ha;
ll memoA[101], memoH[1001];
ll cnt(ll h, ll a, ll d) {
	ll x = d >= a ? 1 : a - d;
	return (h + x - 1) / x;
}
// snapshots

ll S[101][4][1001][4];

int main() {
	std::cin >> N;
	std::cin >> A >> D >> H;
	std::cin >> MA >> MD >> MH;
	std::cin >> Ap >> Aa >> Dp >> Da >> Hp >> Ha;
	S[MA][MD][MH][1] = A;
	S[MA][MD][MH][2] = D;
	S[MA][MD][MH][3] = H;

	int a = MA, h = MH;
	while (!memoA[a]) a = memoA[a] = (p(a, Ap) + Aa) % 100 + 1;
	while (!memoH[h]) h = memoH[h] = (p(h, Hp) + Ha) % 1000 + 1;

	for (int i = 1, jump = 0; i <= N; ++i) {
		if (cnt(MH, A, MD) > cnt(H, MA, D)) {
			std::cout << -1;
			return 0;
		}
		A += MA; D += MD; H += MH;
		MA = memoA[MA];
		MD = (MD - (~MD & ~Dp & 1) + Da) % 3 + 1;
		MH = memoH[MH];

		// cycle detected
		if (!jump && S[MA][MD][MH][1]) {
			// std::cout << "cycle detected!\n";
			jump = 1;
			int period = i - S[MA][MD][MH][0];
			int cycles = (N - i) / period;
			A += (A - S[MA][MD][MH][1]) * cycles;
			D += (D - S[MA][MD][MH][2]) * cycles;
			H += (H - S[MA][MD][MH][3]) * cycles;
			N -= cycles * period;
		}
		S[MA][MD][MH][0] = i;
		S[MA][MD][MH][1] = A;
		S[MA][MD][MH][2] = D;
		S[MA][MD][MH][3] = H;
	}
	std::cout << A % MOD << ' ' << D % MOD << ' ' << H % MOD;
}