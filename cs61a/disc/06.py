
def memory(n):
    """
    >>> f = memory(10)
    >>> f(lambda x: x * 2)
    20
    >>> f(lambda x: x - 7)
    13
    >>> f(lambda x: x > 5)
    True
    """
    def f(g):
        nonlocal n
        n = g(n)
        return n
    return f


s1 = [1, 2, 3]
s2 = s1
print(s1 is s2)  # True

s2.extend([5, 6])
print(s1[4])  # 6

s1.append([-1, 0, 1])
print(s2[5])  # [-1, 0, 1]

s3 = s2[:]
s3.insert(3, s2.pop(3))

print(len(s1))  # 5
# s1 is s2 = [1, 2, 3, 6, [-1, 0, 1]]

print(s1[4] is s3[6])  # True

print(s3[s2[4][1]])  # 1 S3[0]

print(s1[:3] is s2[:3])  # False
print(s1[:3] == s2[:3])  # True


def group_by(s, fn):
    """
    >>> group_by([12, 23, 14, 45], lambda p: p // 10)
    {1: [12, 14], 2: [23], 4: [45]}
    >>> group_by(range(-3, 4), lambda x: x * x)
    {0: [0], 1: [-1, 1], 4: [-2, 2], 9: [-3, 3]}
    """
    grouped = {}
    for i in s:
        key = fn(i)
        if key in grouped:
            grouped[key].append(i)
        else:
            grouped[key] = [i]
    return grouped

def add_this_many(x, el, s):
    """ Adds el to the end of s the number of times x occurs
    in s.
    >>> s = [1, 2, 4, 2, 1]
    >>> add_this_many(1, 5, s)
    >>> s
    [1, 2, 4, 2, 1, 5, 5]
    >>> s = []
    >>> add_this_many(2, 2, s)
    >>> s
    [1, 2, 4, 2, 1, 5, 5, 2, 2]
    """
    count = s.count(x)
    for _ in range(count):
        s.append(el)

s = [1, 2, 4, 2, 1]
add_this_many(1, 5, s)
print(s)

def filter(iterable, fn):
    """
    >>> is_even = lambda x: x % 2 == 0
    >>> list(filter(range(5), is_even)) # a list of the values yielded from the call to filter
    [0, 2, 4]
    >>> all_odd = (2*y-1 for y in range(5))
    >>> list(filter(all_odd, is_even))
    []
    >>> naturals = (n for n in range(1, 100))
    >>> s = filter(naturals, is_even)
    >>> next(s)
    2
    >>> next(s)
    4
    """
    for i in iterable:
        if fn(i):
            yield i

is_even = lambda x: x % 2 == 0
naturals = (n for n in range(1, 100))
s = filter(naturals, is_even)
print(next(s))
print(next(s))

def merge(a, b):
    """
    >>> def sequence(start, step):
    ...     while True:
    ...         yield start
    ...         start += step
    >>> a = sequence(2, 3) # 2, 5, 8, 11, 14, ...
    >>> b = sequence(3, 2) # 3, 5, 7, 9, 11, 13, ...
    >>> result = merge(a, b) # 2, 3, 5, 7, 8, 9, 11, 13, 14, 15
    >>> [next(result) for _ in range(10)]
    [2, 3, 5, 7, 8, 9, 11, 13, 14, 15]
    """
    a_val, b_val = next(a), next(b)
    while True:
        if a_val < b_val:
            yield a_val
            a_val = next(a)
        elif b_val < a_val:
            yield b_val
            b_val = next(b)
        else:
            yield a_val
            a_val, b_val = next(a), next(b)

def sequence(start, step):
    while True:
        yield start
        start += step

a = sequence(2, 3) # 2, 5, 8, 11, 14, ...
b = sequence(3, 2) # 3, 5, 7, 9, 11, 13, ...
result = merge(a, b) # 2, 3, 5, 7, 8, 9, 11, 13, 14, 15
print([next(result) for _ in range(10)])