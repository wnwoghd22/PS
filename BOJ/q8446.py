n = int(input())
ret = 1
if ~n & 1: ret += 2; n -= 1
while n: ret += 2; n //= 2
print(ret)