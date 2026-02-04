import random

n = 10**5 * 2
m = 10**18
print(n)

for i in range(n):
    print(random.randint(0, m), random.randint(0, m))
