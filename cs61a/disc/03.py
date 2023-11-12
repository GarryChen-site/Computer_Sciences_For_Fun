
def multiply(m, n):

    if n == 1:
        return m
    else:
        return m + multiply(m, n - 1)

print(multiply(5, 3))

def hailstone(n):

    if n == 1:
        return 1
    elif n % 2 == 0:
        return 1 + hailstone(n // 2)
    else:
        return 1 + hailstone(3 * n + 1)
    

print(hailstone(10))

def merge(n1, n2):
    """
    Merges two numbers

    >>> merge(31, 42)
    4321
    >>> merge(21, 0)
    21
    >>> merge (21, 31)
    3211
    """
    if n1 == 0:
        return n2
    elif n2 == 0:
        return n1
    elif n1 % 10 < n2 % 10:
        return n1 % 10 + 10 * merge(n1 // 10, n2)
    else:
        return n2 % 10 + 10 * merge(n1, n2 // 10)
    
print(merge(31, 42))


def make_func_repeater(f, x):
    """
    Returns a function that takes one argument and
    calls f on that argument x times.

    >>> incr_1 = make_func_repeater(increment, 1)
    >>> incr_1(2)
    3
    >>> incr_1(5)
    6
    """
    def repeat(y):
        if y <= 1:
            return f(x)
        else:
            return f(repeat(y - 1))
    return repeat

def is_prime(n):
    """
    >>> is_prime(7)
    True
    >>> is_prime(10)
    False
    """
    def prime_helper(i):
        if i == n:
            return True
        elif i == n:
            return True
        elif n % i == 0:
            return False
        else:
            return prime_helper(i + 1)
    return prime_helper(2)