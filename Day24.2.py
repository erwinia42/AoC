from sympy import *

with open("input.txt") as fp:
    stones = [[[int(v) for v in val.split(",")] for val in row.split(" @ ")] for row in fp.read().split("\n")]


x, y, z, vx, vy, vz, t1, t2, t3 = symbols("x, y, z, vx, vy, vz, t1, t2, t3")
eq1 = Eq(x + t1 * vx - stones[0][0][0] - t1 * stones[0][1][0], 0)
eq2 = Eq(x + t2 * vx - stones[1][0][0] - t2 * stones[1][1][0],0)
eq3 = Eq(x + t3 * vx - stones[2][0][0] - t3 * stones[2][1][0], 0)
eq4 = Eq(y + t1 * vy - stones[0][0][1] - t1 * stones[0][1][1], 0)
eq5 = Eq(y + t2 * vy - stones[1][0][1] - t2 * stones[1][1][1], 0)
eq6 = Eq(y + t3 * vy - stones[2][0][1] - t3 * stones[2][1][1], 0)
eq7 = Eq(z + t1 * vz - stones[0][0][2] - t1 * stones[0][1][2], 0)
eq8 = Eq(z + t2 * vz - stones[1][0][2] - t2 * stones[1][1][2], 0)
eq9 = Eq(z + t3 * vz - stones[2][0][2] - t3 * stones[2][1][2], 0)
sol = solve([eq1, eq2, eq3, eq4, eq5, eq6, eq7, eq8, eq9], [x, y, z, vx, vy, vz, t1, t2, t3])

print(sol)
soln = [tuple(v.evalf() for v in s) for s in sol]
print(soln)
print(sum(sol[0][:3]))
