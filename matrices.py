from sys import stdin
from copy import deepcopy
from functools import reduce
from itertools import permutations
import math


class MatrixError(Exception):
    def __init__(self, matrix1, matrix2):
        self.matrix1 = matrix1
        self.matrix2 = matrix2


class Matrix:
    def __init__(self, p):
        self.p = deepcopy(p)

    def __str__(self):
        s = ''
        for i in self.p:
            for j in i:
                s += str(j) + '\t'
            s = s[0:-1]
            s += '\n'
        return s.rstrip()

    def size(self):
        return (len(self.p), len(self.p[0]))

    def __add__(self, t):
        if len(self.p) == len(t.p) and len(self.p[0]) == len(t.p[0]):
            d = []
            u = 0
            for i in self.p:
                q = list(map(lambda r, j: r + j, i, t.p[u]))
                u += 1
                d.append(q)
            return Matrix(d)
        else:
            raise MatrixError(self, t)

    def __mul__(self, al):
        if type(al) == Matrix or type(al) == SquareMatrix:
            d = []
            q = []
            if len(self.p[0]) == (len(al.p)):
                al = Matrix.transposed(al)
                for i in self.p:
                    for j in al.p:
                        r = reduce(lambda a, b: a + b, list(map(lambda x, y: x * y, i, j)))
                        q.append(r)
                    d.append(q)
                    q = []
                return Matrix(d)
            else:
                raise MatrixError(self, al)
        else:
            d = []
            for i in self.p:
                d.append(list(map(lambda x: x*al, i)))
            return Matrix(d)

    def transpose(self):
        d = []
        r = []
        for i in range(len(self.p[0])):
            for j in self.p:
                r.append(j[i])
            d.append(r)
            r = []
        self.p = d
        return Matrix(self.p)

    @staticmethod
    def transposed(y):
        d = []
        r = []
        for i in range(len(y.p[0])):
            for j in y.p:
                r.append(j[i])
            d.append(r)
            r = []
        return Matrix(d)

    def solve(self, t):
        q = []
        d = det(self.p)
        if d != 0:
            for i in range(len(self.p)-1):
                m = Matrix.transposed(self)
                m.p[i] = t
                q.append(det(m.p)/d)
            for h, i in enumerate(self.p):
                if i[len(self.p)-1] != 0:
                    q.append(-sum(list(map(lambda x, y: x*y, i[:-1], q)))+t[h])
                    break
        else:
            raise MatrixError(self, t)
        return q

    __rmul__ = __mul__


def det(t):
    g = 1
    k = 1
    if [0]*(len(t)-1) in t:
        return 0
    else:
        for i in range(len(t)-1):
            while t[i][i] == 0 and i+k < len(t)-1:
                t[i], t[i+k] = t[i+k], t[i]
                k += 1
                g *= -1
            k = 1
            for j in range(i+1, len(t)):
                if t[j][i] == 0:
                    continue
                else:
                    al = -t[j][i]/t[i][i]
                    t[j] = list(map(lambda x, y: x + al*y, t[j], t[i]))
            g *= t[i][i]
        g *= t[-1][-1]
        return g


class SquareMatrix(Matrix):

    def __pow__(self, deg):
        ma1 = deepcopy(self)
        t = 1
        a = []
        if deg == 0:
            for i in range(len(self.p)):
                for j in range(len(self.p[0])):
                    if i == j:
                        self.p[i][j] = 1
                    else:
                        self.p[i][j] = 0
            return Matrix(self.p)
        elif deg == 1:
            return self
        else:
            while deg > 1:
                if deg % 2 == 0:
                    a.append(deg % 2)
                    deg = deg // 2
                else:
                    a.append(1)
                    deg = deg - 1
            a = a[::-1]
            for i in a:
                if i == 1:
                    ma1 = (ma1 * self)
                    t += 1
                else:
                    ma1 = (ma1 * ma1)
                    t *= 2
            return ma1



exec(stdin.read())

# m = SquareMatrix([[1, 0], [0, 1]])
# print(isinstance(m, Matrix))
#
# m = SquareMatrix([[1, 0], [0, 1]])
# print(m ** 0)
m = SquareMatrix([[1, 1, 0, 0, 0, 0],
                  [0, 1, 1, 0, 0, 0],
                  [0, 0, 1, 1, 0, 0],
                  [0, 0, 0, 1, 1, 0],
                  [0, 0, 0, 0, 1, 1],
                  [0, 0, 0, 0, 0, 1]]
                )
m1 = Matrix([[1, 1, 0, 0, 0, 0],
                  [0, 1, 1, 0, 0, 0],
                  [0, 0, 1, 1, 0, 0],
                  [0, 0, 0, 1, 1, 0],
                  [0, 0, 0, 0, 1, 1],
                  [0, 0, 0, 0, 0, 1]]
                )
print(m)
print('----------')
print(m ** 1)
print('----------')
print(m**2)
print('----------')
print(m**3)
print('0'*22+'\n')
print(m ** 4)
print('----------')
print(m ** 5)