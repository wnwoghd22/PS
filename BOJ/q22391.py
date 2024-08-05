def f(x):
    d = []
    while x:
        d.append(x % 10)
        x //= 10
    ret = 0
    for i in range(1, 10):
        for j in range(i + 1, 10):
            for k in range(1, len(d)):
                ret += (1 << k) - 2
            b = 0
            bit = 0
            for k in range(len(d) - 1, -1, -1):
                if k == 0:
                    if bit & 2: ret += d[0] >= i
                    if bit & 1: ret += d[0] >= j
                    break
                if d[k] < i: break
                if d[k] == i:
                    if ~bit & 1: b += 1
                    bit |= 1
                    continue
                c = b + (not (bit & 1))
                ret += (1 << k) - 2 + c
                
                if d[k] < j: break
                if d[k] == j:
                	if ~bit & 2: b += 1
                	bit |= 2
                	continue

                if d[k] > j:
                    c = b + (not (bit & 2))
                    ret += (1 << k) - 2 + c
                    break
	
    for i in range(1, 10):
        for k in range(1, len(d)):
    	    ret += (1 << k - 1) - 1
        if d[-1] > i:
            ret += (1 << len(d) - 1) - 1
        elif d[-1] == i:
            b = 1
            bit = 2
            for k in range(len(d) - 2, -1, -1):
                if k == 0:
                    if bit & 1: ret += d[0] >= i
                    ret += d[0] >= 0
                    break

                if d[k] == 0:
                    if ~bit & 1: b += 1
                    bit |= 1
                    continue

                c = b + (not (bit & 1))
                ret += (1 << k) - 2 + c
				
                if d[k] < i: break
                if d[k] == i: continue
				
                if d[k] > i:
                    c = b + (not (bit & 2))
                    ret += (1 << k) - 2 + c
                    break

    return ret

def solve(n):
    l, r = 10, int(1e60)
    ret = r
    while l <= r:
        m = l + r >> 1
        if f(m) >= n:
            ret = min(ret, m)
            r = m - 1
        else:
            l = m + 1
    return ret

while True:
    n = int(input())
    if n == 0:
        break
    print(f"{solve(n)}")
