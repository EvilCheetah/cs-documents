"""
@file       gcd.py
@author     Eugene Moshchyn
@studentID  113-683-484
@course     CS 5173 - Computer Security
@date       Mar 13th, 2026
@brief      GCD and Mod Inverse Functions
"""

def extended_gcd(a, b):
    """
    Implements the Extended Euclidean Algorithm.
    Returns a tuple (gcd, x, y) such that a*x + b*y = gcd.
    """
    old_r, r = a, b
    old_s, s = 1, 0
    old_t, t = 0, 1

    while r != 0:
        quotient = old_r // r
        old_r, r = r, old_r - quotient * r
        old_s, s = s, old_s - quotient * s
        old_t, t = t, old_t - quotient * t

    return old_r, old_s, old_t

def mod_inverse(a, m):
    """
    Computes the multiplicative inverse of a modulo m using the Extended
    Euclidean Algorithm. Returns the inverse, or None if no inverse exists
    (i.e., gcd(a, m) != 1).
    """
    gcd, x, _ = extended_gcd(a, m)
    if gcd != 1:
        return None  # Modular inverse does not exist
    return x % m
