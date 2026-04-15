def get_factors(number: int) -> list[int]:
    return [
        i
        for i in range(1, number + 1)
        if number % i == 0
    ]
