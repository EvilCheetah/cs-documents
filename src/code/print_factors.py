import math


def get_factors(number: int) -> list[int]:
    factors = set()

    for i in range(1, int(math.sqrt(number)) + 1):
        if number % i == 0:
            factors.add(i)
            factors.add(number // i)

    return sorted(list(factors))
