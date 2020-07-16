import decimal
import math
import sys


def main():
    decimal.getcontext().prec = 170
    line = sys.stdin.readline()
    one_third = (decimal.Decimal(1) / decimal.Decimal(3))

    while line:
        n = int(line)
        print(round(decimal.Decimal(n) ** one_third ))
        line = sys.stdin.readline()

if __name__ == "__main__":
    main()
