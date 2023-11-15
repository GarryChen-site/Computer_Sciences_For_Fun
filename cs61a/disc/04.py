
def count_stair_ways(n):
    """Count the number of ways to climb up a flight of n stairs,
    moving either 1 step or 2 steps at a time.
    >>> count_stair_ways(4)
    5
    >>> count_stair_ways(5)
    8
    """
    if n == 1:
        return 1
    elif n == 2:
        return 2
    else:
        return count_stair_ways(n-1) + count_stair_ways(n-2)
    
def count_k(n, k):
    """Count the number of ways to climb up a flight of n stairs,
    moving up either 1, 2, 3, ..., or k steps at a time.
    >>> count_k(3, 3)
    4
    >>> count_k(4, 4)
    8
    >>> count_k(10, 3)
    274
    >>> count_k(300, 1) # Only one step at a time
    1
    """
    if n == 0:
        return 1
    elif n < 0:
        return 0
    else:
        total = 0
        for i in range(1, k+1):
            total += count_k(n-i, k)
        return total

a = [1, 5, 4, [2, 3], 3]

# a[0] == 1 a[-1] == 3
# len(a) == 5
# 2 in a == False
# 4 in a == True
# a[3][0] = 2

def even_weighted(s):
    list = []
    for i in range(len(s)):
        if i % 2 == 0:
            list.append(s[i] * i)

    return list

def max_product(s):
    """Return the maximum product that can be formed using non-consecutive
    elements of s.
    >>> max_product([10,3,1,9,2]) # 10 * 9
    90
    >>> max_product([5,10,5,10,5]) # 5 * 5 * 5
    125
    >>> max_product([])
    1
    """
    if len(s) == 0:
        return 1
    else:
        return max(s[0] * max_product(s[2:]), max_product(s[1:]))
    