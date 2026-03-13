"""
@file       main.py
@author     Eugene Moshchyn
@studentID  113-683-484
@course     CS 5173 - Computer Security
@date       Mar 13th, 2026
@brief      Main Functions
"""


from tabulate import tabulate
from gcd import ( extended_gcd, mod_inverse )


def main():
    print("--- Extended Euclidean Algorithm Results ---")
    
    data = [
        [
            "a",
            "GCD",
            10012012,
            2314213,
            extended_gcd(10012012, 2314213)[0]
        ],
        [
            "b",
            "GCD",
            28176412,
            29108188,
            extended_gcd(28176412, 29108188)[0]
        ],
        [
            "c",
            "GCD",
            38172,
            23812188,
            extended_gcd(38172, 23812188)[0]
        ],
        ["d",
            "Inverse",
            12091,
            24123123,
            mod_inverse(12091, 24123123)
        ],
        ["e",
            "Inverse",
            28173928,
            129182771,
            mod_inverse(28173928, 129182771)
        ],
        ["f",
            "GCD",
            381723029127918237717233210002,
            23812188332813212739187261,
            extended_gcd(381723029127918237717233210002, 23812188332813212739187261)[0]
        ]
    ]
    
    headers = ["Item", "Type", "Input A", "Input B / Mod", "Result"]

    print(tabulate(data, headers=headers, tablefmt="grid"))


if __name__ == '__main__':
    main()
