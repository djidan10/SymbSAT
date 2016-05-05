"""
DIMACS Reading
"""

from poly import Poly
from ring import BoolPolyRing


def _parse_line(line, x):

    _1 = Poly.one

    indexes = tuple(map(int, line.split()))

    # initial value of the acc
    i_ = abs(indexes[0]) - 1

    if indexes[0] < 0:
        p = (x[i_] + _1)
    else:
        p = x[i_]

    for i in indexes[1:]:

        # end of clause
        if i == 0:
            break

        i_ = abs(i) - 1

        if i < 0:
            v = (x[i_] + _1)
        else:
            v = x[i_]

        # p = p + v + p*v
        p = p*v

    return p


def load(filename):

    num_vars = 0
    num_clauses = 0
    # Boolean Ring
    B = None
    # list with variables
    x = []
    # list with polynomials
    P = []

    for line in open(filename, 'r'):

        if line.startswith('c'):
            print(line.strip())
            continue

        if line.startswith('p'):
            print(line.strip())
            _line = line.split()
            assert _line[1] == 'cnf'

            num_vars = int(_line[2])
            num_clauses = int(_line[3])

            B = BoolPolyRing(num_vars)
            x = B.gens

            continue

        # accumulate clauses
        if line.endswith('0\n') or line.endswith('0'):
            p = _parse_line(line, x)
            P.append(p)

    assert num_clauses == len(P)

    return P, B