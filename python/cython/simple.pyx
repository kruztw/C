import math 


def add_p(a, b, c):
    return a + b + c

cdef public int add_c(int a, int b, int c):
    return a + b + c

cpdef public int add_cp(int a, int b, int c):
    return a + b + c
