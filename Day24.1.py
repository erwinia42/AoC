import numpy as np

with open("24.in") as fp:
    stones = [[[int(v) for v in val.split(",")] for val in row.split(" @ ")] for row in fp.read().split("\n")]

n = len(stones)
low = 200000000000000
hi = 400000000000000
count = 0

for i in range(n):
    stone1 = stones[i]
    for j in range(i+1, n):
        stone2 = stones[j]
        vars = np.array([[stone1[1][0], -stone2[1][0]],
                         [stone1[1][1], -stone2[1][1]]])
        ans = np.array([[stone2[0][0] - stone1[0][0]],
                        [stone2[0][1] - stone1[0][1]]])

        try:
            times = np.linalg.solve(vars, ans)
        except Exception:
            continue

        if any(t <= 0 for t in times):
            continue

        x1 = stone1[0][0] + times[0] * stone1[1][0]
        y1 = stone1[0][1] + times[0] * stone1[1][1]

        x2 = stone2[0][0] + times[1] * stone2[1][0]
        y2 = stone2[0][1] + times[1] * stone2[1][1]


        if all([low <= v <= hi for v in [x1, y1, x2, y2]]):
            count += 1

print(count)
