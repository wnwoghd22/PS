#include <iostream>
#include <algorithm>

int N, a, b, c;
int main() {
	std::cin >> N >> a >> b;

	std::cout << (int)log2(a - 1 ^ b - 1) + 1 << '\n';

	--a, --b;
	while (a ^ b) ++c, a >>= 1, b >>= 1;
	std::cout << c;
}

// main(a,b,c){for(scanf("%d%d%d",&a,&b,&c),a=0,--b,--c;b^c;++a)b>>=1,c>>=1;printf("%d",a);}
// a;main(b,c){for(scanf("%d%d%d",&b,&b,&c),b=b-1^c-1;b;++a)b/=2;printf("%d",a);}
// main(i,j){scanf("%d%d%d",&i,&i,&j);printf("%d",log2(i-1^j-1)+1);}