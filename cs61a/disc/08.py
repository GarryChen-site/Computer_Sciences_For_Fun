
from link import Link
from tree import Tree
from operator import mul


class A():
    def __init__(self, x):
        self.x = x
    def __repr__(self):
        return self.x
    def __str__(self):
        return self.x * 2


class B():
    def __init__(self):
        print("boo!")
        self.a = []
    def add_a(self, a):
        self.a.append(a)
    def __repr__(self):
        print(len(self.a))
        ret = ""
        for a in self.a:
            ret += str(a)
        return ret

A("one")

print(A("one"))

repr(A("two")) 

b = B()

b.add_a(A("a"))
b.add_a(A("b"))

b

def sum_nums(link):
    if link.rest == Link.empty:
        return link.first
    return link.first + sum_nums(link.rest)

a = Link(1, Link(6, Link(7)))
print(sum_nums(a))

def multiply_lnks(lst_of_lnks):
    val = 1
    new_lst = []
    for lnk in lst_of_lnks:
        if lnk == Link.empty:
            return Link.empty
        val *= lnk.first
        new_lst.append(lnk.rest)
    return Link(val, multiply_lnks(new_lst))

def flip_two(lnk):
    if lnk == Link.empty or lnk.rest == Link.empty:
        return lnk
    else:
        return Link(lnk.rest.first, Link(lnk.first, flip_two(lnk.rest.rest)))

lnk = Link(1, Link(2, Link(3, Link(4, Link(5)))))
print(lnk)
print(flip_two(lnk)) # Link(2, Link(1, Link(4, Link(3, Link(5)))))

def filter_link(link, f):
    if link == Link.empty:
        return
    if f(link.first):
        yield link.first
    yield from filter_link(link.rest, f)

link = Link(1, Link(2, Link(3)))
g = filter_link(link, lambda x: x % 2 == 0)
print(list(g))
print(list(filter_link(link, lambda x: x % 2 != 0)))

def make_even(t):
    if t.label % 2 != 0:
        t.label += 1
    
    if Tree.is_leaf(t):
        return
    
    for b in t.branches:
        make_even(b)

t = Tree(1, [Tree(2, [Tree(3)]), Tree(4, [Tree(5)])])
make_even(t)
Tree.print_tree(t)

def square_tree(t):

    t.label = t.label ** 2

    if Tree.is_leaf(t):
        return

    for b in t.branches:
        square_tree(b)
    
def find_paths(t, entry):
    lst = []

    def helper(t, entry, cur_lst=[]):
        cur_lst.append(t.label)

        if t.label == entry:
            lst.append(cur_lst)

        if Tree.is_leaf(t):
            return
        
        for b in t.branches:
            new_lst = cur_lst[:]
            helper(b, entry, new_lst)
        
    helper(t, entry)
    return lst


tree_ex = Tree(
    2, [Tree(7, [Tree(3), Tree(6, [Tree(5), Tree(11)])]), Tree(1, [Tree(5)])]
)

print(find_paths(tree_ex, 5))

def combine_tree(t1, t2, combiner):
    if Tree.is_leaf(t1):
        return Tree(combiner(t1.label, t2.label))
    return Tree(
        combiner(t1.label, t2.label), 
        [combine_tree(b1, b2, combiner) for b1, b2 in zip(t1.branches, t2.branches)]
        )

a = Tree(1, [Tree(2, [Tree(3)])])
b = Tree(4, [Tree(5, [Tree(6)])])
print("combine_tree: ")
Tree.print_tree(combine_tree(a, b, mul))

def alt_tree_map(t, map_fn):
    def helper(t, map_fn, level=0):
        if level % 2 == 0:
            t.label = map_fn(t.label)
        if Tree.is_leaf(t):
            return
        for b in t.branches:
            helper(b, map_fn, level + 1)
    helper(t, map_fn)

t = Tree(1, [Tree(2, [Tree(3)]), Tree(4)])
alt_tree_map(t, lambda x: -x)
print("alt_tree_map: ")
Tree.print_tree(t)
