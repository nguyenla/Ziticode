import decimal
import math
import sys


def main():
    decimal.getcontext().prec = 1000
    line = sys.stdin.readline()

    while line:
        n = int(line)
        print((round(decimal.Decimal(n) ** (decimal.Decimal(1) / decimal.Decimal(3)))))
        line = sys.stdin.readline()

if __name__ == "__main__":
    main()
