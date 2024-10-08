#include <iostream>

int a1, a0, c, n0;

int main() {
	std::cin >> a1 >> a0 >> c >> n0;
	std::cout << (c < a1 ? 0 : a1 * n0 + a0 <= c * n0);
	printf("%d", c < a1 ? 0 : a0 <= (c - a1) * n0);
	int ret = 0;
	if (c < a1) ret = 0;
	else ret = a1 * n0 + a0 <= c * n0;
	std::cout << ret;
}
// main(a,b,c,d){scanf("%d%d%d%d",&a,&b,&c,&d);prinf("%d",c<a?0:b<(c-a)*d);}